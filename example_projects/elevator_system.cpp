#include <iostream>
#include <thread>
#include <queue>
#include <list>
#include <map>

enum class State
{
    GOING_UP,
    GOING_DOWN,
    IDLE
};

std::map<State, std::string> StateMap = {
    {State::GOING_UP, "GOING_UP"},
    {State::GOING_DOWN, "GOING_DOWN"},
    {State::IDLE, "IDLE"}
};

enum class ElevatorType
{
    PASSENGER,
    SERVICE
};

enum class RequestOrigin
{
    OUTSIDE,
    INSIDE
};

enum class DoorState
{
    OPEN,
    CLOSED
};

std::map<DoorState, std::string> DoorStateMap = {
    {DoorState::OPEN, "OPEN"},
    {DoorState::CLOSED, "CLOSED"}
};

class Request
{
protected:
    RequestOrigin origin;
    State direction;
    int originFloor;
    int destinationFloor;
    ElevatorType elevatorType;

public:
    // Constructor for requests from outside the elevator
    Request(RequestOrigin origin, int originFloor, int destinationFloor)
        : origin(origin), originFloor(originFloor), destinationFloor(destinationFloor), elevatorType(ElevatorType::PASSENGER)
    {

        if (originFloor > destinationFloor)
        {
            direction = State::GOING_DOWN;
        }
        else if (originFloor < destinationFloor)
        {
            direction = State::GOING_UP;
        }
        else
        {
            direction = State::IDLE;
        }
    }

    // Constructor for requests from inside the elevator
    Request(RequestOrigin origin, int destinationFloor)
        : origin(origin), destinationFloor(destinationFloor), direction(State::IDLE), elevatorType(ElevatorType::PASSENGER)
    {
    }

    int getOriginFloor() const
    {
        return originFloor;
    }

    int getDestinationFloor() const
    {
        return destinationFloor;
    }

    RequestOrigin getOrigin() const
    {
        return origin;
    }

    State getDirection() const
    {
        return direction;
    }
};

class ServiceRequest : public Request
{
public:
    ServiceRequest(RequestOrigin origin, int currentFloor, int destinationFloor)
        : Request(origin, currentFloor, destinationFloor)
    {
        elevatorType = ElevatorType::SERVICE;
    }

    ServiceRequest(RequestOrigin origin, int destinationFloor)
        : Request(origin, destinationFloor)
    {
        elevatorType = ElevatorType::SERVICE;
    }
};

class Elevator
{
protected:
    int currentFloor;
    State state;
    bool emergencyStatus;
    DoorState doorState;

public:
    Elevator(int currentFloor, bool emergencyStatus)
        : currentFloor(currentFloor), state(State::IDLE), emergencyStatus(emergencyStatus), doorState(DoorState::CLOSED)
    {
    }

    void openDoors()
    {
        doorState = DoorState::OPEN;
        std::cout << "Doors are OPEN on floor " << currentFloor << std::endl;
    }

    void closeDoors()
    {
        doorState = DoorState::CLOSED;
        std::cout << "Doors are CLOSED" << std::endl;
    }

    virtual void operate() = 0; // Pure virtual function

    virtual void processEmergency() = 0;

    int getCurrentFloor() const
    {
        return currentFloor;
    }

    State getState() const
    {
        return state;
    }

    void setState(State state)
    {
        this->state = state;
    }

    void setCurrentFloor(int currentFloor)
    {
        this->currentFloor = currentFloor;
    }

    DoorState getDoorState() const
    {
        return doorState;
    }

    void setEmergencyStatus(bool status)
    {
        emergencyStatus = status;
    }

    virtual ~Elevator() {}
};

class PassengerElevator : public Elevator
{
private:
    std::priority_queue<Request *, std::vector<Request *>, std::function<bool(Request *, Request *)>> passengerUpQueue;
    std::priority_queue<Request *, std::vector<Request *>, std::function<bool(Request *, Request *)>> passengerDownQueue;

public:
    PassengerElevator(int currentFloor, bool emergencyStatus)
        : Elevator(currentFloor, emergencyStatus),
          passengerUpQueue([](Request *a, Request *b)
                           { return a->getDestinationFloor() > b->getDestinationFloor(); }),
          passengerDownQueue([](Request *a, Request *b)
                             { return a->getDestinationFloor() < b->getDestinationFloor(); })
    {
    }

    void operate() override
    {
        while (!passengerUpQueue.empty() || !passengerDownQueue.empty())
        {
            processRequests();
        }
        this->setState(State::IDLE);
        std::cout << "All requests have been fulfilled, elevator is now " << StateMap[this->getState()] << std::endl;
    }

    void processEmergency() override
    {
        while (!passengerUpQueue.empty())
            passengerUpQueue.pop();
        while (!passengerDownQueue.empty())
            passengerDownQueue.pop();

        this->setCurrentFloor(1);
        this->setState(State::IDLE);
        this->openDoors();
        this->setEmergencyStatus(true);
        std::cout << "Queues cleared, current floor is " << this->getCurrentFloor() << ". Doors are " << DoorStateMap[this->getDoorState()] << std::endl;
    }

    void addUpRequest(Request *request)
    {
        if (request->getOrigin() == RequestOrigin::OUTSIDE)
        {
            Request *pickUpRequest = new Request(request->getOrigin(), request->getOriginFloor(), request->getOriginFloor());
            passengerUpQueue.push(pickUpRequest);
        }
        passengerUpQueue.push(request);
    }

    void addDownRequest(Request *request)
    {
        if (request->getOrigin() == RequestOrigin::OUTSIDE)
        {
            Request *pickUpRequest = new Request(request->getOrigin(), request->getOriginFloor(), request->getOriginFloor());
            passengerDownQueue.push(pickUpRequest);
        }
        passengerDownQueue.push(request);
    }

    void processUpRequests()
    {
        while (!passengerUpQueue.empty())
        {
            Request *upRequest = passengerUpQueue.top();
            passengerUpQueue.pop();

            if (this->getCurrentFloor() == upRequest->getDestinationFloor())
            {
                std::cout << "Currently on floor " << this->getCurrentFloor() << ". No movement as destination is the same." << std::endl;
                continue;
            }
            std::cout << "The current floor is " << this->getCurrentFloor() << ". Next stop: " << upRequest->getDestinationFloor() << std::endl;

            std::cout << "Moving ";
            for (int i = 0; i < 3; i++)
            {
                std::cout << ".";
            }

            this->setCurrentFloor(upRequest->getDestinationFloor());
            std::cout << "\nArrived at " << this->getCurrentFloor() << std::endl;

            this->openDoors();
            this->closeDoors();
        }
        std::cout << "Finished processing all the up requests." << std::endl;
    }

    void processDownRequests()
    {
        while (!passengerDownQueue.empty())
        {
            Request *downRequest = passengerDownQueue.top();
            passengerDownQueue.pop();

            if (this->getCurrentFloor() == downRequest->getDestinationFloor())
            {
                std::cout << "Currently on floor " << this->getCurrentFloor() << ". No movement as destination is the same." << std::endl;
                continue;
            }
            std::cout << "The current floor is " << this->getCurrentFloor() << ". Next stop: " << downRequest->getDestinationFloor() << std::endl;

            std::cout << "Moving ";
            for (int i = 0; i < 3; i++)
            {
                std::cout << ".";
            }

            this->setCurrentFloor(downRequest->getDestinationFloor());
            std::cout << "\nArrived at " << this->getCurrentFloor() << std::endl;

            this->openDoors();
            this->closeDoors();
        }
        std::cout << "Finished processing all the down requests." << std::endl;
    }

    void processRequests()
    {
        if (this->getState() == State::GOING_UP || this->getState() == State::IDLE)
        {
            processUpRequests();
            if (!passengerDownQueue.empty())
            {
                std::cout << "Now processing down requests..." << std::endl;
                processDownRequests();
            }
        }
        else
        {
            processDownRequests();
            if (!passengerUpQueue.empty())
            {
                std::cout << "Now processing up requests..." << std::endl;
                processUpRequests();
            }
        }
    }
};

class ServiceElevator : public Elevator
{
private:
    std::list<ServiceRequest *> serviceQueue;

public:
    ServiceElevator(int currentFloor, bool emergencyStatus)
        : Elevator(currentFloor, emergencyStatus) {}

    void operate() override
    {
        while (!serviceQueue.empty())
        {
            ServiceRequest *currRequest = serviceQueue.front();
            serviceQueue.pop_front();

            std::cout << std::endl
                      << "Currently at " << this->getCurrentFloor() << std::endl;
            try
            {
                std::cout << StateMap[currRequest->getDirection()];
                for (int i = 0; i < 3; i++)
                {
                    std::cout << ".";
                }
            }
            catch (const std::exception &e)
            {
                // Handle the exception here
                std::cerr << e.what() << std::endl;
            }
            this->setCurrentFloor(currRequest->getDestinationFloor());
            this->setState(currRequest->getDirection());
            std::cout << "Arrived at " << this->getCurrentFloor() << std::endl;
            this->openDoors();
            this->closeDoors();
        }
        this->setState(State::IDLE);
        std::cout << "All requests have been fulfilled, elevator is now " << StateMap[this->getState()] << std::endl;
    }

    void addRequestToQueue(ServiceRequest *request)
    {
        serviceQueue.push_back(request);
    }

    void processEmergency() override
    {
        serviceQueue.clear();
        this->setCurrentFloor(1);
        this->setState(State::IDLE);
        this->openDoors();
        this->setEmergencyStatus(true);
        std::cout << "Queue cleared, current floor is " << this->getCurrentFloor() << ". Doors are " << DoorStateMap[this->getDoorState()] << std::endl;
    }
};

class ElevatorFactory {
public:
    Elevator* createElevator(ElevatorType type) {
        switch (type) {
            case ElevatorType::PASSENGER:
                return new PassengerElevator(1, false);
            case ElevatorType::SERVICE:
                return new ServiceElevator(1, false);
            default:
                throw std::invalid_argument("Unknown criteria.");
        }
    }
};

class Controller
{
private:
    ElevatorFactory *factory;
    PassengerElevator *passengerElevator;
    ServiceElevator *serviceElevator;

public:
    Controller(ElevatorFactory *factory)
        : factory(factory)
    {
        passengerElevator = dynamic_cast<PassengerElevator *>(factory->createElevator(ElevatorType::PASSENGER));
        serviceElevator = dynamic_cast<ServiceElevator *>(factory->createElevator(ElevatorType::SERVICE));
    }

    void sendPassengerUpRequests(Request *request)
    {
        passengerElevator->addUpRequest(request);
    }

    void sendPassengerDownRequests(Request *request)
    {
        passengerElevator->addDownRequest(request);
    }

    void sendServiceRequest(ServiceRequest *request)
    {
        serviceElevator->addRequestToQueue(request);
    }

    void handlePassengerRequests()
    {
        passengerElevator->operate();
    }

    void handleServiceRequests()
    {
        serviceElevator->operate();
    }

    void handleEmergency()
    {
        passengerElevator->processEmergency();
        serviceElevator->processEmergency();
    }
};


int main()
{
    ElevatorFactory factory;
    Controller controller(&factory);

    controller.sendPassengerUpRequests(new Request(RequestOrigin::OUTSIDE, 1, 5));
    controller.sendPassengerDownRequests(new Request(RequestOrigin::OUTSIDE, 4, 2));
    controller.sendPassengerUpRequests(new Request(RequestOrigin::OUTSIDE, 3, 6));
    controller.handlePassengerRequests();

    controller.sendPassengerUpRequests(new Request(RequestOrigin::OUTSIDE, 1, 9));
    controller.sendPassengerDownRequests(new Request(RequestOrigin::INSIDE, 5));
    controller.sendPassengerUpRequests(new Request(RequestOrigin::OUTSIDE, 4, 12));
    controller.sendPassengerDownRequests(new Request(RequestOrigin::OUTSIDE, 10, 2));
    controller.handlePassengerRequests();

    std::cout << "Now processing service requests" << std::endl;

    controller.sendServiceRequest(new ServiceRequest(RequestOrigin::INSIDE, 13));
    controller.sendServiceRequest(new ServiceRequest(RequestOrigin::OUTSIDE, 13, 2));
    controller.sendServiceRequest(new ServiceRequest(RequestOrigin::INSIDE, 13, 15));

    controller.handleServiceRequests();

    return 0;
}
