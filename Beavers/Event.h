#pragma once
#include <functional>

using std::function;
using std::bind;

/*
	Event that allows specific Return types and Parameter Types

	@author Jamuel Bocacao
*/
template<class Return, class ParamA, class ParamB>
class Event2P
{
public:
	template<class T>
	Event2P(T* _instance, Return(T::* _function)(ParamA, ParamB));

	Return execute(ParamA _paramA, ParamB _paramB);

private:
	function<Return(ParamA, ParamB)> m_function;
};

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
	Creates an Event that uses 2 parameters using a class instance and one of its functions
	Return refers to return type of function
	ParamA refers to the first parameter type that is pass to the function when called
	ParamB refers to the first parameter type that is pass to the function when called

	@param T*: Pointer to any Class Instance
	@param T::*: Pointer to a function owned by the Class Instance
*/
template<class Return, class ParamA, class ParamB>
template<class T>
inline Event2P<Return, ParamA, ParamB>::Event2P(T* _instance, Return(T::* _function)(ParamA, ParamB))
{
	m_function = std::bind(_function, _instance, std::placeholders::_1, std::placeholders::_2);
}

/*
	Creates an Event that uses 1 parameter using a class instance and one of its functions
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
	Executes an Event with two parameters

	@param ParamA: First Parameter Type to pass into Event when called
	@param ParamB: Second Parameter Type to pass into Event when called
	@return Return: Return type of Event
*/
template<class Return, class ParamA, class ParamB>
inline Return Event2P<Return, ParamA, ParamB>::execute(ParamA _paramA, ParamB _paramB)
{
	return m_function(_paramA, _paramB);
}

/*
	Creates an Event that uses 1 parameter using a class instance and one of its functions
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
