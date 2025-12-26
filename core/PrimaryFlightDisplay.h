#pragma once
#include <QWidget>
#include "FlightData.h"
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>

class PrimaryFlightDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit PrimaryFlightDisplay(QWidget *parent = nullptr);
    void updateFlightData(const FlightData &data);

protected:
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override { return QSize(800, 600); }
    QSize minimumSizeHint() const override { return QSize(600, 450); }

private:
    FlightData flightData_;

    void drawArtificialHorizon(QPainter &painter, const QRectF &bounds);
    void drawPitchLadder(QPainter &painter, const QRectF &bounds);
    void drawAirspeedTape(QPainter &painter, const QRectF &bounds);
    void drawAltitudeTape(QPainter &painter, const QRectF &bounds);
    void drawHeadingIndicator(QPainter &painter, const QRectF &bounds);
    void drawCenterReference(QPainter &painter, const QRectF &bounds);
};