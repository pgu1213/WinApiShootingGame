#pragma once

template<typename T>
class IDataProvider {
public:
    virtual const T& GetData() const abstract;
};