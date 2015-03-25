// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// This copy of Ice Protobuf is licensed to you under the terms
// described in the ICE_PROTOBUF_LICENSE file included in this
// distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <TestCommon.h>
#include <Test.h>
#include <Test.pb.h>

using namespace std;
using namespace Test;

class CallbackBase : public Ice::LocalObject
{
public:

    CallbackBase() :
        _called(false)
    {
    }

    virtual ~CallbackBase()
    {
    }

    void check()
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock sync(_m);
        while(!_called)
        {
            _m.wait();
        }
        _called = false;
    }

protected:

    void called()
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock sync(_m);
        assert(!_called);
        _called = true;
        _m.notify();
    }

private:

    IceUtil::Monitor<IceUtil::Mutex> _m;
    bool _called;
};

typedef IceUtil::Handle<CallbackBase> CallbackBasePtr;


class Callback : public CallbackBase
{
public:

    Callback()
    {
    }

    void opMessage(const test::Message& r, const test::Message& o)
    {
        test(o.i() == 99);
        test(r.i() == 99);
        called();
    }

    void opMessageAMD(const test::Message& r, const test::Message& o)
    {
        test(o.i() == 99);
        test(r.i() == 99);
        called();
    }

    void exCB(const Ice::Exception& ex)
    {
        try
        {
            ex.ice_throw();
        }
        catch (const Ice::OperationNotExistException&)
        {
            called();
        }
        catch(const Ice::Exception&)
        {
            test(false);
        }
    }
};
typedef IceUtil::Handle<Callback> CallbackPtr;

MyClassPrx
allTests(const Ice::CommunicatorPtr& communicator)
{
    string ref = "test:default -p 12010";
    Ice::ObjectPrx baseProxy = communicator->stringToProxy(ref);
    MyClassPrx cl = MyClassPrx::checkedCast(baseProxy);
    test(cl);

    cout << "testing twoway operations... " << flush;
    {
        test::Message i;
        i.set_i(99);
        test::Message o;

        test::Message r = cl->opMessage(i, o);

        test(o.i() == 99);
        test(r.i() == 99);
    }
    {
        test::Message i;
        i.set_i(99);
        test::Message o;

        test::Message r = cl->opMessageAMD(i, o);

        test(o.i() == 99);
        test(r.i() == 99);
    }
    cout << "ok" << endl;

    cout << "testing twoway AMI operations... " << flush;
    {
        {
            test::Message i;
            i.set_i(99);

            CallbackPtr cb = new Callback;
            cl->begin_opMessage(i,
                                [=](const test::Message& r, const test::Message& o)
                                {
                                    cb->opMessage(r, o);
                                },
                                [=](const Ice::Exception& ex){ cb->exCB(ex); });
            cb->check();
        }
        {
            test::Message i;
            i.set_i(99);

            CallbackPtr cb = new Callback;
            cl->begin_opMessageAMD(i,
                                [=](const test::Message& r, const test::Message& o)
                                {
                                    cb->opMessageAMD(r, o);
                                },
                                [=](const Ice::Exception& ex) { cb->exCB(ex); });
            cb->check();
        }
    }
    cout << "ok" << endl;

    return cl;
}
