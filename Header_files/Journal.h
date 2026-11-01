#pragma once
#include "Publication.h"

class Journal : public Publication {
private:
    int volumeNumber;
    std::string publisher;
public:
    Journal(std::string_view t = "", std::string_view a = "", int y = 2022, int volume = 1, std::string_view pub = "Издательство", std::weak_ptr<ScientificLibrary> lib = {});

    int getVolumeNumber() const;
    void setVolumeNumber(int volume);
    void printVolumeNumber(std::ostream& os) const;
    void readVolumeNumber(std::istream& is);

    std::string_view getPublisher() const;
    void setPublisher(std::string_view pub);
    void printPublisher(std::ostream& os) const;
    void readPublisher(std::istream& is);

    // Уникальный метод журнала
    void nextVolume();

    std::string_view getType() const override;
    void printInformation(std::ostream& os) const override;
    void readFrom(std::istream& is) override;
    double getKeyIndicator() const override;
    std::string getKeyIndicatorName() const override;
    void updateKeyIndicator(int value) override;
    bool equals(const Publication& other) const override;
};
