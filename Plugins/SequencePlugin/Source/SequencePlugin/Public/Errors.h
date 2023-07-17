#pragma once


enum ErrorType
{
	NotFound,
	ResponseParseError,
	EmptyResponse,
	UnsupportedMethodOnChain,
	RequestFail,
	RequestTimeExceeded,


	UnknownError,
};

class SequenceError
{
public:
	SequenceError();
	SequenceError(ErrorType Type, FString Message);
	FString Message;
	ErrorType Type;
};

template<typename T> using TResult = TValueOrError<T, SequenceError>;
