#include "Errors.h"

SequenceError::SequenceError() : Message(""), Type(UnknownError)
{
}

SequenceError::SequenceError(ErrorType Type, FString Message) : Message(Message), Type(Type)
{
}
