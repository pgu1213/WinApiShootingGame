#pragma once
class CObject
{
protected:
    CObject(const string& Name = "Object");

public:
    virtual void Init();
    virtual void Update(float DeltaTime);
    virtual void Release();

    unsigned int GetObjectID() const; // 오브젝트 ID 반환
    const string& GetObjectName() const; // 오브젝트 이름 반환
    bool IsValid() const; // 객체가 유효한지 확인

private:
    atomic<unsigned int> m_NextObjectID; // 다음 출력을 위한 임시 UID
    unsigned int m_ObjectID; // 임시 UID
    string m_ObjectName;     // 객체의 이름
    bool m_bIsValid; // 객체가 유효한 상태인지?
};
