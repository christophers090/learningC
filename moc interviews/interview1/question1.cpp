#include <iostream>

struct SensorReading
{
    double value;

    // its in a struct so by default this will be callable, public.
    double getValue() const
    {
        return value;
    }
};

void processReading(const SensorReading &reading)
{
    // This function receives a *constant* reference,
    // meaning it promises not to change the 'reading' object.
    // We need to be able to call getValue() on the 'reading' object.
    // double currentValue = reading.getValue();
    // std::cout << "Processing value: " << currentValue << std::endl;

    std::cout << "(Inside processReading - assuming getValue() can be called)" << std::endl;
}

int main()
{
    SensorReading currentSensor = {98.6};
    std::cout << "Initial value: " << currentSensor.value << std::endl;
    processReading(currentSensor);
    // Example of calling the getter if it exists and is callable:
    // std::cout << "Value from getter: " << currentSensor.getValue() << std::endl;
    return 0;
}