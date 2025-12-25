#include <QtFlightDataObserver.h>

QtFlightDataObserver::QtFlightDataObserver(QWidget *parent) : QWidget(parent)
{
    layout_ = new QVBoxLayout(this);
    altitudeLabel_ = new QLabel("Altitude: --", this);
    speedLabel_ = new QLabel("Speed: --", this);
    headingLabel_ = new QLabel("Heading: --", this);
    autopilotLabel_ = new QLabel("Autopilot: --", this);

    layout_->addWidget(altitudeLabel_);
    layout_->addWidget(speedLabel_);
    layout_->addWidget(headingLabel_);
    layout_->addWidget(autopilotLabel_);

    setLayout(layout_);
}

void QtFlightDataObserver::onFlightDataChanged(const FlightData &data)
{
    altitudeLabel_->setText(QString("Altitude: %1 ft").arg(data.altitude_ft));
    speedLabel_->setText(QString("Speed: 1% kt").arg(data.ias_kt));
    headingLabel_->setText(QString("Heading: %1").arg(data.heading_deg));
}

void QtFlightDataObserver::onAutopilotChanged(const AutopilotTargets &targets, bool engaged)
{
    QString status = engaged ? "ON" : "OFF";
    QString text = QString("AP: %1 | ALT: %2 ft | IAS: %3 kt | HDG: %4 ")
                       .arg(status)
                       .arg(targets.altitude_ft)
                       .arg(targets.ias_kt)
                       .arg(targets.heading_deg);
}