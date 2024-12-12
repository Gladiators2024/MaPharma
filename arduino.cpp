#include "arduino.h"

arduino::arduino()
{
    serial = nullptr;
    arduino_is_available = false;
    arduino_port_name = "";
}

int arduino::connect_arduino() {
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
            serial_port_info.productIdentifier() == arduino_uno_producy_id) {
            arduino_is_available = true;
            arduino_port_name = serial_port_info.portName();
            break; // Exit loop once Arduino is found
        }
    }

    if (arduino_is_available) {
        serial = new QSerialPort;
        serial->setPortName(arduino_port_name);

        // Configure and open the serial port
        if (serial->open(QIODevice::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600); // Match with Arduino sketch
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            return 0; // Success
        } else {
            delete serial;
            serial = nullptr;
            return -2; // Failed to open port
        }
    } else {
        return -1; // Arduino not found
    }
}

int arduino::close_arduino() {
    if (serial != nullptr && serial->isOpen()) {
        serial->close();
        delete serial;
        serial = nullptr;
        return 0; // Successfully closed
    }
    return -1; // Serial port not open or doesn't exist
}

QByteArray arduino::read_from_arduino() {
    if (serial != nullptr && serial->isOpen()) {
        data = serial->readAll();
        return data;
    }
    return QByteArray(); // Return empty data if serial not available
}

void arduino::write_to_arduino(QByteArray data) {
    if (serial != nullptr && serial->isOpen()) {
        serial->write(data);
    }
}


QSerialPort* arduino::getserial() {
    return serial;
}

QString arduino::getarduino_port_name() {
    return arduino_port_name;
}

arduino::~arduino() {
    close_arduino();
}
