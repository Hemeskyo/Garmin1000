#include "PrimaryFlightDisplay.h"

PrimaryFlightDisplay::PrimaryFlightDisplay(QWidget *parent) : QWidget(parent)
{
    flightData_ = {};
    setMinimumSize(600, 450);
}

void PrimaryFlightDisplay::updateFlightData(const FlightData &data)
{
    flightData_ = data;
    update();
}

void PrimaryFlightDisplay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRectF bounds = rect();

    drawArtificialHorizon(painter, bounds);
    drawAirspeedTape(painter, bounds);
    drawAltitudeTape(painter, bounds);
    drawCenterReference(painter, bounds);
    drawHeadingIndicator(painter, bounds);
    drawHeadingIndicator(painter, bounds);
    drawPitchLadder(painter, bounds);
}

void PrimaryFlightDisplay::drawArtificialHorizon(QPainter &painter, const QRectF &bounds)
{
    painter.save();

    // Horizon area
    QPointF center(bounds.width() / 2, bounds.height() / 2);
    double horizonWidth = bounds.width() * 0.6;
    double horizonHeight = bounds.height() * 0.7;

    QPainterPath clipPath;
    clipPath.addEllipse(center, horizonWidth / 2, horizonHeight / 2);
    painter.setClipPath(clipPath);

    // Translate and rotate
    painter.translate(center);
    painter.rotate(-flightData_.roll_deg);

    // Pitch offset
    double pixelsPerDegree = horizonHeight / 60.0;
    double pitchOffset = flightData_.pitch_deg * pixelsPerDegree;

    // Sky => upper
    QLinearGradient skyGradient(0, -horizonHeight, 0, pitchOffset);
    skyGradient.setColorAt(0, QColor(0, 100, 200));   // blue
    skyGradient.setColorAt(1, QColor(100, 180, 255)); // lighter blue
    painter.fillRect(QRectF(-horizonWidth, -horizonHeight * 2, horizonWidth * 2, horizonHeight * 2 + pitchOffset), skyGradient);

    // Sky => lower
    QLinearGradient groundGradient(0, pitchOffset, 0, horizonHeight);
    skyGradient.setColorAt(0, QColor(139, 90, 43)); // borwn
    skyGradient.setColorAt(1, QColor(101, 67, 33)); // darker  brown
    painter.fillRect(QRectF(-horizonWidth, pitchOffset, horizonWidth * 2, horizonHeight * 2), groundGradient);

    // Horizon line
    painter.setPen(QPen(Qt::white, 3));
    painter.drawLine(QPointF(-horizonWidth, pitchOffset), QPointF(horizonWidth, pitchOffset));

    painter.restore();
}

void PrimaryFlightDisplay::drawPitchLadder(QPainter &painter, const QRectF &bounds)
{
    painter.save();

    QPointF center(bounds.width() / 2, bounds.height() / 2);
    double horizonHeight = bounds.height() * 0.7;
    double pixelsPerDegree = horizonHeight / 60.0;

    QPainterPath clipPath;
    clipPath.addEllipse(center, bounds.width() * 0.3, horizonHeight / 2);
    painter.setClipPath(clipPath);

    painter.translate(center);
    painter.rotate(-flightData_.roll_deg);

    double pitchOffset = flightData_.pitch_deg * pixelsPerDegree;

    painter.setPen(QPen(Qt::white, 2));
    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);

    for (int pitch = -90; pitch <= 90; pitch += 10)
    {
        if (pitch == 0)
            continue;

        double y = pitchOffset - pitch * pixelsPerDegree;
        double lineWidth = (pitch % 10 == 0) ? 80 : 40;

        painter.drawLine(QPointF(-lineWidth, y), QPointF(lineWidth, y));

        // Pitch indicator
        if (pitch % 10 == 0)
        {
            QString text = QString::number(std::abs(pitch));
            painter.drawText(QPointF(-lineWidth - 30, y + 5), text);
            painter.drawText(QPointF(lineWidth + 10, y + 5), text);
        }
    }
    painter.restore();
}

void PrimaryFlightDisplay::drawAirspeedTape(QPainter &painter, const QRectF &bounds)
{
    painter.save();

    double tapeX = 20;
    double tapeY = bounds.height() * 0.2;
    double tapeWidth = 80;
    double tapeHeight = bounds.height() * 0.6;

    // Background
    painter.fillRect(QRectF(tapeX, tapeY, tapeWidth, tapeHeight), QColor(30, 30, 30, 200));
    painter.setPen(QPen(Qt::white, 2));
    painter.drawRect(QRectF(tapeX, tapeY, tapeWidth, tapeHeight));

    // Draw speed markings
    double pixelsPerKnot = tapeHeight / 80.0; // 80 knot range visible
    double centerY = tapeY + tapeHeight / 2;

    painter.setClipRect(QRectF(tapeX, tapeY, tapeWidth, tapeHeight));

    int minSpeed = static_cast<int>(flightData_.ias_kt - 40);
    int maxSpeed = static_cast<int>(flightData_.ias_kt + 40);

    for (int speed = (minSpeed / 10) * 10; speed <= maxSpeed; speed += 10)
    {
        if (speed < 0)
            continue;

        double y = centerY - (speed - flightData_.ias_kt) * pixelsPerKnot;
        painter.drawLine(QPointF(tapeX + tapeWidth - 15, y), QPointF(tapeX + tapeWidth, y));

        QString text = QString::number(speed);
        painter.drawText(QRectF(tapeX + 5, y - 10, tapeWidth - 25, 20), Qt::AlignLeft | Qt::AlignVCenter, text);
    }

    painter.setClipping(false);

    // Current speed box
    painter.fillRect(QRectF(tapeX, centerY - 20, tapeWidth, 40), Qt::black);
    painter.setPen(QPen(Qt::cyan, 2));
    painter.drawRect(QRectF(tapeX, centerY - 20, tapeWidth, 40));

    QFont font = painter.font();
    font.setPointSize(16);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QRectF(tapeX, centerY - 20, tapeWidth, 40), Qt::AlignCenter, QString::number(static_cast<int>(flightData_.ias_kt)));

    painter.restore();
}

void PrimaryFlightDisplay::drawAltitudeTape(QPainter &painter, const QRectF &bounds)
{
    painter.save();

    double tapeWidth = 100;
    double tapeX = bounds.width() - tapeWidth - 20;
    double tapeY = bounds.height() * 0.2;
    double tapeHeight = bounds.height() * 0.6;

    // Background
    painter.fillRect(QRectF(tapeX, tapeY, tapeWidth, tapeHeight), QColor(30, 30, 30, 200));
    painter.setPen(QPen(Qt::white, 2));
    painter.drawRect(QRectF(tapeX, tapeY, tapeWidth, tapeHeight));

    // Draw altitude markings
    double pixelsPerFoot = tapeHeight / 500.0; // 500 ft range visible
    double centerY = tapeY + tapeHeight / 2;

    painter.setClipRect(QRectF(tapeX, tapeY, tapeWidth, tapeHeight));

    int minAlt = static_cast<int>((flightData_.altitude_ft - 250) / 100) * 100;
    int maxAlt = static_cast<int>((flightData_.altitude_ft + 250) / 100) * 100;

    for (int alt = minAlt; alt <= maxAlt; alt += 100)
    {
        double y = centerY - (alt - flightData_.altitude_ft) * pixelsPerFoot;
        painter.drawLine(QPointF(tapeX, y), QPointF(tapeX + 15, y));

        QString text = QString::number(alt / 100);
        painter.drawText(QRectF(tapeX + 20, y - 10, tapeWidth - 25, 20), Qt::AlignLeft | Qt::AlignVCenter, text);
    }

    painter.setClipping(false);

    // Current altitude box
    painter.fillRect(QRectF(tapeX, centerY - 20, tapeWidth, 40), Qt::black);
    painter.setPen(QPen(Qt::cyan, 2));
    painter.drawRect(QRectF(tapeX, centerY - 20, tapeWidth, 40));

    QFont font = painter.font();
    font.setPointSize(16);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QRectF(tapeX, centerY - 20, tapeWidth, 40), Qt::AlignCenter, QString::number(static_cast<int>(flightData_.altitude_ft)));

    painter.restore();
}

void PrimaryFlightDisplay::drawHeadingIndicator(QPainter &painter, const QRectF &bounds)
{
    painter.save();

    double tapeWidth = bounds.width() * 0.6;
    double tapeHeight = 60;
    double tapeX = (bounds.width() - tapeWidth) / 2;
    double tapeY = bounds.height() - tapeHeight - 10;

    // Background
    painter.fillRect(QRectF(tapeX, tapeY, tapeWidth, tapeHeight), QColor(30, 30, 30, 200));
    painter.setPen(QPen(Qt::white, 2));
    painter.drawRect(QRectF(tapeX, tapeY, tapeWidth, tapeHeight));

    // Draw heading markings
    double pixelsPerDegree = tapeWidth / 60.0; // 60 degrees visible range
    double centerX = tapeX + tapeWidth / 2;

    painter.setClipRect(QRectF(tapeX, tapeY, tapeWidth, tapeHeight));

    for (int hdg = 0; hdg < 360; hdg += 5)
    {
        double offset = hdg - flightData_.heading_deg;

        // Normalize to -180 to 180
        while (offset > 180)
            offset -= 360;
        while (offset < -180)
            offset += 360;

        if (std::abs(offset) > 30)
            continue;

        double x = centerX + offset * pixelsPerDegree;

        if (hdg % 30 == 0)
        {
            painter.drawLine(QPointF(x, tapeY), QPointF(x, tapeY + 20));
            QString text;
            if (hdg == 0)
                text = "N";
            else if (hdg == 90)
                text = "E";
            else if (hdg == 180)
                text = "S";
            else if (hdg == 270)
                text = "W";
            else
                text = QString::number(hdg / 10);

            painter.drawText(QRectF(x - 20, tapeY + 25, 40, 30), Qt::AlignCenter, text);
        }
        else if (hdg % 10 == 0)
        {
            painter.drawLine(QPointF(x, tapeY), QPointF(x, tapeY + 15));
        }
        else
        {
            painter.drawLine(QPointF(x, tapeY), QPointF(x, tapeY + 10));
        }
    }

    painter.setClipping(false);

    // Current heading indicator (triangle at top)
    painter.setBrush(Qt::cyan);
    QPainterPath triangle;
    triangle.moveTo(centerX, tapeY);
    triangle.lineTo(centerX - 10, tapeY + 15);
    triangle.lineTo(centerX + 10, tapeY + 15);
    triangle.closeSubpath();
    painter.drawPath(triangle);

    // Current heading box
    double boxWidth = 80;
    painter.fillRect(QRectF(centerX - boxWidth / 2, tapeY + tapeHeight - 30, boxWidth, 25), Qt::black);
    painter.setPen(QPen(Qt::cyan, 2));
    painter.drawRect(QRectF(centerX - boxWidth / 2, tapeY + tapeHeight - 30, boxWidth, 25));

    QFont font = painter.font();
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);
    int hdg = static_cast<int>(flightData_.heading_deg) % 360;
    painter.drawText(QRectF(centerX - boxWidth / 2, tapeY + tapeHeight - 30, boxWidth, 25), Qt::AlignCenter, QString("%1°").arg(hdg, 3, 10, QChar('0')));

    painter.restore();
}

void PrimaryFlightDisplay::drawCenterReference(QPainter &painter, const QRectF &bounds)
{
    painter.save();

    QPointF center(bounds.width() / 2, bounds.height() / 2);

    // Draw the aircraft symbol (center reference)
    painter.setPen(QPen(Qt::yellow, 4));
    painter.setBrush(Qt::NoBrush);

    // Center dot
    painter.drawEllipse(center, 5, 5);

    // Wings
    painter.drawLine(QPointF(center.x() - 80, center.y()), QPointF(center.x() - 20, center.y()));
    painter.drawLine(QPointF(center.x() + 80, center.y()), QPointF(center.x() + 20, center.y()));

    // Wing tips
    painter.drawLine(QPointF(center.x() - 80, center.y()), QPointF(center.x() - 80, center.y() + 15));
    painter.drawLine(QPointF(center.x() + 80, center.y()), QPointF(center.x() + 80, center.y() + 15));

    painter.restore();
}