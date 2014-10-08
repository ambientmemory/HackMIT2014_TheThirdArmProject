#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>
#include <myo/myo.hpp>
#include <Windows.h>
#include "myodata.h"
#include "SerialPort.hpp"

class MyoListener : public myo::DeviceListener {
public:
    MyoListener(SerialPort& serialPort)
    : _serialPort(serialPort)
    {
    }

    // Every time the SDK successfully pairs with a Myo armband, this function will be called.
    //
    // You can rely on the following rules:
    //  - onPair() will only be called once for each Myo device
    //  - no other events will occur involving a given Myo device before onPair() is called with it
    //
    // If you need to do some kind of per-Myo preparation before handling events, you can safely do it in onPair().
    void onPair(myo::Myo* myo, uint64_t timestamp)
    {
        // Print out the MAC address of the armband we paired with.

        // The pointer address we get for a Myo is unique - in other words, it's safe to compare two Myo pointers to
        // see if they're referring to the same Myo.

        // Add the Myo pointer to our list of known Myo devices. This list is used to implement identifyMyo() below so
        // that we can give each Myo a nice short identifier.
        knownMyos.push_back(myo);

        // Now that we've added it to our list, get our short ID for it and print it out.
        std::cout << "Paired with " << myo->macAddressAsString() << ", now known as Myo " << identifyMyo(myo)
            << "." << std::endl;

        // Check whether this Myo device has been trained. It will only provide pose information if it's been trained.
        if (myo->isTrained()) {
            std::cout << "Myo " << identifyMyo(myo) << " is trained and will provide pose events." << std::endl;
        }
        else {
            std::cout << "Myo " << identifyMyo(myo) << " is not trained and will not provide any pose events."
                << std::endl;
        }
    }

    void onConnect(myo::Myo* myo, uint64_t timestamp)
    {
        std::cout << "Myo " << identifyMyo(myo) << " has connected." << std::endl;
    }

    void onDisconnect(myo::Myo* myo, uint64_t timestamp)
    {
        std::cout << "Myo " << identifyMyo(myo) << " has disconnected." << std::endl;
    }

    void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
    {
        myodata_event_pose_t evt;
        evt.event_type = static_cast<uint8_t>(myodata_event_pose);
        evt.myo_id = identifyMyo(myo);
        evt.pose = static_cast<uint16_t>(pose.type());

        _serialPort.WriteData(reinterpret_cast<char*>(&evt), sizeof(evt));
    }

    void onOrientationData(myo::Myo* myo, uint64_t timestamp, myo::Quaternion<float> quat)
    {
        using std::atan2;
        using std::asin;
        using std::sqrt;

        // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
        float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
                           1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
        float pitch = asin(2.0f * (quat.w() * quat.y() - quat.z() * quat.x()));
        float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
                          1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));

        myodata_event_orientation_t evt;
        evt.event_type = myodata_event_orientation;
        evt.myo_id = identifyMyo(myo);
        evt.roll = static_cast<int16_t>(roll * RPY_SCALE);
        evt.pitch = static_cast<int16_t>(pitch * RPY_SCALE);
        evt.yaw = static_cast<int16_t>(yaw * RPY_SCALE);

        _serialPort.WriteData(reinterpret_cast<char*>(&evt), sizeof(evt));
    }

private:
    SerialPort& _serialPort;

    // We store each Myo pointer that we pair with in this list, so that we can keep track of the order we've seen
    // each Myo and give it a unique short identifier (see onPair() and identifyMyo() above).
    std::vector<myo::Myo*> knownMyos;

    // This is a utility function implemented for this sample that maps a myo::Myo* to a unique ID starting at 1.
    // It does so by looking for the Myo pointer in knownMyos, which onPair() adds each Myo into as it is paired.
    uint8_t identifyMyo(myo::Myo* myo)
    {
        // Walk through the list of Myo devices that we've seen pairing events for.
        for (size_t i = 0; i < knownMyos.size(); ++i) {
            // If two Myo pointers compare equal, they refer to the same Myo device.
            if (knownMyos[i] == myo) {
                return static_cast<uint8_t>(i + 1);
            }
        }

        return 0;
    }
};

int main(int argc, char** argv)
{
    const char* portName = "COM4";

    // Open the serial port.
    SerialPort serialPort(portName);

    // Make sure the serial port has connected successfully.
    if (serialPort.IsConnected()) {
        std::cout << "Serial port is connected on " << portName << "." << std::endl;
    } else {
        std::cerr << "Serial port failed to connected." << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return 1;
    }

    try {
        const unsigned int pairingCount = 2;

        myo::Hub hub;

        std::cout << "Pairing with " << pairingCount << " Myo armbands." << std::endl;

        // pairWithAnyMyos() asynchronously initiates the pairing process with the provided number of Myo devices.
        // DeviceListeners attached to the hub will receive onPair() events once pairing has completed.
        hub.pairWithAnyMyos(pairingCount);

        MyoListener listener(serialPort);
        hub.addListener(&listener);

        while (1) {
            // Process events for 10 milliseconds at a time.
            hub.run(10);
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return 1;
    }
}
