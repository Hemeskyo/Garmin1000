#pragma once
#include "IFlightDataObserver.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class QtFlightDataObserver : public QWidget, public IFlightDataObserver
{
    Q_OBJECT

public:
    explicit QtFlightDataObserver(QWidget *parent = nullptr);
    ~QtFlightDataObserver() override = default;
    virtual void onFlightDataChanged(const FlightData &data) override;
    virtual void onAutopilotChanged(const AutopilotTargets &targets, bool engaged) override;

private:
    QLabel *altitudeLabel_;
    QLabel *speedLabel_;
    QLabel *headingLabel_;
    QLabel *autopilotLabel_;
    QVBoxLayout *layout_;
};