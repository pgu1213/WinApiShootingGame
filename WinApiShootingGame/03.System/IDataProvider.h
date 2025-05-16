#pragma once

template<typename T>
class IDataProvider {
public:
    virtual T& GetData() const = 0;
};