/*
MIT No Attribution

Copyright 2022 Aidan Lee

Permission is hereby granted, free of charge, to any person obtaining a copy of this
software and associated documentation files (the "Software"), to deal in the Software
without restriction, including without limitation the rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <hxcpp.h>
#include "utils/RootedObject.hpp"

cpp::utils::RootedObject::RootedObject()
    : rooted(new hx::Object*(nullptr))
{
    refCount = 1;
    hx::GCAddRoot(rooted);
}

cpp::utils::RootedObject::RootedObject(void* _baton)
    : rooted(static_cast<hx::Object**>(_baton))
{
    refCount = 1;
    //
}

cpp::utils::RootedObject::RootedObject(hx::Object** _root)
    : rooted(_root)
{
    refCount = 1;
    //
}

cpp::utils::RootedObject::RootedObject(hx::Object* _object)
    : rooted(new hx::Object*(_object))
{
    refCount = 1;
    hx::GCAddRoot(rooted);
}

cpp::utils::RootedObject::~RootedObject()
{
    if (rooted != nullptr) {
        hx::GCRemoveRoot(rooted);
        delete rooted;
    }
}

void cpp::utils::RootedObject::prepareRemoval() 
{
    if (refCount == 1) {
        hx::GCRemoveRoot(rooted);
    }
    rooted = nullptr;
}

int cpp::utils::RootedObject::incRef() 
{
    return ++refCount;
}

int cpp::utils::RootedObject::decRef() 
{
    return --refCount;
}

hx::Object** cpp::utils::RootedObject::getObjectPtr() const
{
    return rooted;
}

cpp::utils::RootedObject::operator hx::Object*() const
{
    return *rooted;
}

hx::Object* cpp::utils::RootedObject::getObject() const
{
    return *rooted;
}

void cpp::utils::RootedObject::setObject(hx::Object* _object) const
{
    *rooted = _object;
}