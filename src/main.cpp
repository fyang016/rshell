// Franklin Yang
// lab 2


// Given specification, design a system
// Use vim

// Submit your code: 1) ilearn 
// OR
// email at darvisha@cs.ucr.edu
// Deadline: Friday 5pm
// THursday 1:00 pm

// Compile:
// g++ test.c -o test
// ./test

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Vehicle {
    private:
        double speed_per_hour;
        string vehicleName;
        
    public:
        
        void inputSpeed(double speed)
        {
            speed_per_hour = speed;
        }
        
        void inputVehicleName(string vName)
        {
            vehicleName = vName;
        }
        
        double getSpeed()
        {
            return speed_per_hour;
        }
        
        string getVehicleName()
        {
            return vehicleName;
        }
        
        // Output name of vehicle 
        void go(double timeHours)
        {
            cout << vehicleName << ": " << timeHours * speed_per_hour << endl;
        }
};

class Land: public Vehicle {
    private:
        int number_of_wheels;
        int number_of_seats;
    
    public:
        void modify_wheels(int numWheels)
        {
            number_of_wheels = numWheels;
        }
        
        void modify_seats(int numSeats)
        {
            number_of_seats = numSeats;
        }
        
        int check_wheels()
        {
            return number_of_wheels;
        }
        
        int check_seats()
        {
            return number_of_seats;
        }
};

class Air: public Vehicle {
    private:
        
    public:
        
};

class Water: public Vehicle {
    private:
        int number_of_seats;
        int number_of_doors;
    public:
        void modify_seats(int numSeats)
        {
            number_of_seats = numSeats;
        }
        void modify_doors(int numDoors)
        {
            number_of_doors = numDoors;
        }
        int check_seats()
        {
            return number_of_seats;
        }
        int check_doors()
        {
            return number_of_doors;
        }
};


class Bus: public Land {
    
    private:
        int number_of_doors;
        double fare;
        
    public:
        
        Bus()
        {
            number_of_doors = 2;
            modify_seats(40);
            modify_wheels(6);
            fare = 1.25;
            inputSpeed(50);
            inputVehicleName("Bus");
        }
        
};

class Coup: public Land {
    
    private:
        int number_of_doors;
        
    public:
        Coup()
        {
            number_of_doors = 2;
            modify_seats(4);
            modify_wheels(4);
            inputSpeed(120);
            inputVehicleName("Coup");
        }
    
};

class Sedan: public Land {
    private:
        int number_of_doors;
    
    public:
        Sedan()
        {
            number_of_doors = 4;
            modify_seats(4);
            modify_wheels(4);
            inputSpeed(100);
            inputVehicleName("Sedan");
        }
};

class Motorcycle: public Land {
    private:
        
    public:
        Motorcycle()
        {
            modify_seats(1);
            modify_wheels(2);
            inputSpeed(80);
            inputVehicleName("Motorcycle");
        }
};

class Bicycle: public Land {
    private:
        
    public:
        Bicycle()
        {
            modify_seats(1);
            modify_wheels(2);
            inputSpeed(25.25);
            inputVehicleName("Bicycle");
        }
};

// The hover board, implied by its name, should be an air vehicle.
// However, it has wheels, so that makes it that the two provided air vehicles
// have only speed in common.
class Hoverboard: public Air {
    private:
        int number_of_wheels;
    public:
        Hoverboard()
        {
            number_of_wheels = 4;
            inputSpeed(30.00);
            inputVehicleName("Hover board");
        }
        
};

class Paddleboat: public Water {
    private:
        string shape_of_boat;
    public:
        Paddleboat()
        {
            modify_seats(2);
            modify_doors(2);
            inputSpeed(10.00);
            shape_of_boat = "swan";
            inputVehicleName("Paddleboat");
        }
};

class FalconRocket: public Air {
    private:
        int number_of_seats;
        int number_of_doors;
        int tons_of_fuel;
        int tons_of_payload;
        
    public:
        FalconRocket()
        {
            number_of_seats = 6;
            number_of_doors = 1;
            tons_of_fuel = 9000;
            tons_of_payload = 2000;
            inputSpeed(2112662.054);
            inputVehicleName("Falcon Rocket");
        }
        
};

class Airplane: public Air {
    private:
        int number_of_seats;
        int number_of_doors;
        int number_of_wheels;
    public:
        Airplane()
        {
            number_of_seats = 500;
            number_of_doors = 6;
            number_of_wheels = 18
            inputSpeed(550);
            inputVehicleName("Passenger Plane");
        }
};

class Forklift: public Land {
    private:
        int max_weight_kg;
    public:
        Forklift()
        {
            modify_seats(1);
            modify_wheels(4);
            max_weight_kg = 10000;
            inputSpeed(25);
            inputVehicleName("Forklift");
        }
};

class Jet: public Air {
    private:
        int number_of_seats;
    public:
        Jet()
        {
            number_of_seats = 2;
            inputSpeed(7200);
            inputVehicleName("Jet");
        }
};

int main()
{
    vector<Vehicle> vehicleVector;
    Bus bus1;
    Coup coup1;
    Sedan sedan1;
    Motorcycle motorcycle1;
    Bicycle bicycle1;
    Hoverboard hoverboard1;
    Paddleboat paddleboat1;
    FalconRocket falconrocket1;
    
    Airplane airplane1;
    Forklift forklift1;
    Jet jet1;
    
    vehicleVector.push_back(bus1);
    vehicleVector.push_back(coup1);
    vehicleVector.push_back(sedan1);
    vehicleVector.push_back(motorcycle1);
    vehicleVector.push_back(bicycle1);
    vehicleVector.push_back(hoverboard1);
    vehicleVector.push_back(paddleboat1);
    vehicleVector.push_back(falconrocket1);
    
    vehicleVector.push_back(airplane1);
    vehicleVector.push_back(forklift1);
    vehicleVector.push_back(jet1);
    
    int inputTime;
    
    cout << "Please input the time: ";
    cin >> inputTime;
    
    for (int i = 0; i < vehicleVector.size(); ++i)
    {
        vehicleVector.at(i).go(inputTime);
    }
    
    return 0;
}


// Part A: Why did you design the system like this?

// SI units?


// Part B: What decisions that you made in part A made it difficult to extend?



// Part C: What did you add, and how is that different from A and B?


// http://www.cplusplus.com/doc/tutorial/inheritance/