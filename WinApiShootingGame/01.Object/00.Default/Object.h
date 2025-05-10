#pragma once
class Object
{
protected:
    Object(const string& Name = "BaseObject");

public:
    virtual void Init();
    virtual void Update(float DeltaSeconds);
    virtual void Release();

    unsigned int GetObjectID() const; // 오브젝트 ID 반환
    const string& GetObjectName() const; // 오브젝트 이름 반환
    bool IsValid() const; // 객체가 유효한지 확인

private:
    static atomic<unsigned int> NextObjectID; // 임시 UID
    unsigned int ObjectID; // 이 객체의 고유 ID
    std::string ObjectName;     // 객체의 이름 (디버깅 또는 식별 목적)
    bool bIsValid; // 객체가 유효한 상태인지 나타내는 플래그 (가비지 컬렉션 유사 개념 시 활용)
};
