#pragma once
#include <functional>

using std::function;
using std::bind;

/*
	Event that allows specific Return types and Parameter Types

	@author Jamuel Bocacao
*/
template<class Return, class Param>
class Event
{
public:
	template<class T>
	Event(T* _instance, Return(T::* _function)(Param));

	Return execute(Param _param);

private:
	function<Return(Param)> m_function;
};

/*
	Event that allows specific Return types

	@author Jamuel Bocacao
*/
template<class Return>
class Event<Return, void>
{
public:
	template<class T>
	Event(T* _instance, Return(T::* _function)());

	Return execute();

private:
	function<Return()> m_function;
};

/*
	Creates an Event using a class instance and one of its functions
	Return refers to return type of function
	Param refers to parameter type that is pass to the function when called

	@param T*: Pointer to any Class Instance
	@param T::*: Pointer to a function owned by the Class Instance
*/
template<class Return, class Param>
template<class T>
inline Event<Return, Param>::Event(T* _instance, Return(T::* _function)(Param))
{
	m_function = bind(_function, _instance, std::placeholders::_1);
}

/*
	Creates an Event using a class instance and one of its functions
	Return refers to return type of function

	@param T*: Pointer to any Class Instance
	@param T::*: Pointer to a function owned by the Class Instance
*/
template<class Return>
template<class T>
inline Event<Return, void>::Event(T* _instance, Return(T::* _function)())
{
	m_function = bind(_function, _instance);
}

/*
	Executes an Event with a parameter

	@param Param: Data to be passed into function
	@return Return: Return type of event
*/
template<class Return, class Param>
inline Return Event<Return, Param>::execute(Param _param)
{
	return m_function(_param);
}

/*
	Executes an Event with no parameters

	@return Return: Return type of event
*/
template<class Return>
inline Return Event<Return, void>::execute()
{
	return m_function();
}
