#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Dispatcher;

class Transport {
protected:
    Dispatcher* dispatcher;
public:
    Transport(Dispatcher* dispatcher) : dispatcher(dispatcher) {}
    virtual void communicate(string message) = 0;
    virtual void send(string message) = 0;
    virtual string toString() const = 0;
};

class Dispatcher {
private:
    vector<Transport*> transports;
public:
    void registerTransport(Transport* transport) {
        transports.push_back(transport);
    }
    void broadcast(string message, Transport* sender) {
        cout << "Диспетчер получил от " << sender->toString() << " сообщение: " << message << endl;
    }
    void send(string message, Transport* receiver) {
        cout << "Диспетчер отправил " << receiver->toString() << " сообщение: " << message << endl;
    }
};

class Boeing : public Transport {
public:
    Boeing(Dispatcher* dispatcher) : Transport(dispatcher) {}
    void communicate(string message) override {
        cout << "Самолет Boeing: " << message << endl;
        dispatcher->broadcast(message, this);
    }
    void send(string message) override {
        cout << "Самолет Boeing отправляет сообщение: " << message << endl;
        dispatcher->send(message, this);
    }
    string toString() const override { return "Самолет Boeing"; }
};

class Airbus : public Transport {
public:
    Airbus(Dispatcher* dispatcher) : Transport(dispatcher) {}
    void communicate(string message) override {
        cout << "Самолет Airbus: " << message << endl;
        dispatcher->broadcast(message, this);
    }
    void send(string message) override {
        cout << "Самолет Airbus отправляет сообщение: " << message << endl;
        dispatcher->send(message, this);
    }
    string toString() const override { return "Самолет Airbus"; }
};

class Cessna : public Transport {
public:
    Cessna(Dispatcher* dispatcher) : Transport(dispatcher) {}
    void communicate(string message) override {
        cout << "Самолет Cessna: " << message << endl;
        dispatcher->broadcast(message, this);
    }
    void send(string message) override {
        cout << "Самолет Cessna отправляет сообщение: " << message << endl;
        dispatcher->send(message, this);
    }
    string toString() const override { return "Самолет Cessna"; }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Dispatcher dispatcher;

    Boeing boeing(&dispatcher);
    Airbus airbus(&dispatcher);
    Cessna cessna(&dispatcher);

    dispatcher.registerTransport(&boeing);
    dispatcher.registerTransport(&airbus);
    dispatcher.registerTransport(&cessna);

    boeing.send("Изменение курса до 20 градусов");
    airbus.communicate("Меняю высоту на 400 метров");
    cessna.send("Предупреждение о турбулентности");

    return 0;
}
