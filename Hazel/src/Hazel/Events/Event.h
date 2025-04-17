//
// Created by tanhao on 2025/4/12.
//

#pragma once

#include<hzpch.h>



#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


#include <Hazel/Core/Core.h>





namespace Hazel
{

    // Events in Hazel are currently blocking, meaning when an event occurs it
    // immediately gets dispatched and must be dealt with right then an there.
    // For the future, a better strategy might be to buffer events in an event
    // bus and process them during the "event" part of the update stage.

    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };
//#enum 类型大小由编译器指定
    enum EventCategory
    {
        None = 0,
        EventCategoryApplication    = BIT(0),
        EventCategoryInput          = BIT(1),
        EventCategoryKeyboard       = BIT(2),
        EventCategoryMouse          = BIT(3),
        EventCategoryMouseButton    = BIT(4)
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
                                virtual EventType GetEventType() const override {return GetStaticType();}\
                                virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }




    class HAZEL_API Event;


    class HAZEL_API Event
    {
        friend class EventDispatcher;
    public:
        virtual ~Event()=default;

        virtual EventType GetEventType() const = 0;//[[nodiscard]]编译器提醒返回值
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

//const
        bool IsInCategory(EventCategory category) const
        {
            return GetCategoryFlags() & category;
        }
        bool Handled =false;
    protected:

    };
//dispatch 发送，派遣，分发

    class EventDispatcher
    {
        template<typename T>
        using EventFn =std::function<bool(T&)>;


    public:
        EventDispatcher(Event& event) //explicit 不会隐式转换
            : m_Event(event)
        {
        }
        // F will be deduced by compiler
        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            if(m_Event.GetEventType()==T::GetStaticType())
            {
                m_Event.Handled  |= func(static_cast<T&>(m_Event));

                return true;
            }
            return false;
        }
    private:
        Event& m_Event;

    };



}


