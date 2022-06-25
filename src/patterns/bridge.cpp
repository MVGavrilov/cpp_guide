// Подробнее в https://refactoring.guru/ru/design-patterns/bridge

#include <iostream>

class Device {
public:
    virtual ~Device() = default;

    virtual bool is_on() const = 0;

    virtual void enable() = 0;

    virtual void disable() = 0;

    virtual void set_volume(int volume) = 0;

    virtual int get_volume() const {
        return volume;
    }

protected:
    int volume;
    bool is_on_;
};

class TV : public Device {
public:
    TV() {
        volume = 0;
        is_on_ = false;
    };

    bool is_on() const override {
        return is_on_;
    }

    void enable() override {
        if (is_on_) {
            std::cout << "TV is already turned on" << std::endl;
        } else {
            std::cout << "TV is turned on" << std::endl;
            is_on_ = true;
        }
    }

    void disable() override {
        if (is_on_) {
            std::cout << "TV is turned off" << std::endl;
            is_on_ = false;
        } else {
            std::cout << "TV is already turned off" << std::endl;
        }
    }

    void set_volume(int volume) override {
        this->volume = volume;
        std::cout << "TV volume is set to " << volume << std::endl;
    }
};

class Radio : public Device {
public:
    Radio() {
        volume = 0;
        is_on_ = false;
    };

    bool is_on() const override {
        return is_on_;
    }

    void enable() override {
        if (is_on_) {
            std::cout << "Radio is already turned on" << std::endl;
        } else {
            std::cout << "Radio is turned on" << std::endl;
            is_on_ = true;
        }
    }

    void disable() override {
        if (is_on_) {
            std::cout << "Radio is turned off" << std::endl;
            is_on_ = false;
        } else {
            std::cout << "Radio is already turned off" << std::endl;
        }
    }

    void set_volume(int volume) override {
        this->volume = volume;
        std::cout << "Radio volume is set to " << volume << std::endl;
    }
};

class RemoteControl {
public:
    explicit RemoteControl(Device *device) {
        this->device = device;
    }

    RemoteControl() = delete;

    void on() {
        device->enable();
    };

    void off() {
        device->disable();
    };

    void volumeUp() {
        if (device->is_on()) {
            if (device->get_volume() < 100) {
                device->set_volume(device->get_volume() + 1);
            }
        }
    };

    void volumeDown() {
        if (device->is_on()) {
            if (device->get_volume() > 0) {
                device->set_volume(device->get_volume() - 1);
            }
        }
    };
private:
    Device *device;
};

int main() {
    TV tv;
    Radio radio;
    RemoteControl tv_remote(&tv);
    RemoteControl radio_remote(&radio);
    tv_remote.on();
    tv_remote.volumeUp();
    tv_remote.volumeDown();
    tv_remote.off();
    radio_remote.on();
    radio_remote.volumeUp();
    radio_remote.volumeDown();
    radio_remote.off();
}