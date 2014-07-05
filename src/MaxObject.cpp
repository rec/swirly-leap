#include "Max.h"
#include "MaxObject.h"
#include "Callback.h"
#include "Gensym.h"
#include "LeapMotion.h"
#include "Split.h"

namespace swirly {
namespace leap {

namespace {

t_class* CLASS_POINTER;

} // namespace

using namespace std::placeholders;

MaxObject::MaxObject(MaxStruct *maxStruct, t_symbol *s, long argc, t_atom *argv)
        : maxStruct_(maxStruct),
          object_(&maxStruct_->object_),
          leap_(new LeapMotion(*this)) {
    log(string(s->s_name) + ", built " __DATE__ ", " __TIME__);

    outlet_ = outlet_new(maxStruct_, nullptr);
    leap_->frameHandler_.setOutlet(outlet_);

    for (auto i = 0; i < argc; ++i) {
        if (argv[i].a_type == A_SYM)
            leap_->config_.addArgument(getSymbol(&argv[i]));
        else
            err("forbidden argument");
    }
    leap_->config_.finishArguments();
}

MaxObject::~MaxObject() {}

void MaxObject::log(string const& message) const {
    auto parts = split(message, '\r');
    for (auto& p: parts)
        object_post(object_, "%s", p.c_str());
}

void MaxObject::err(string const& message) const {
    auto parts = split(message, '\r');
    for (auto& p: parts)
        object_error(object_, "ERROR: %s", p.c_str());
}

void MaxObject::bang() {
    if (!leap_->listener_.sendFrame())
        err("bang: Can't send frame while running.");
}

void MaxObject::setRunning(bool isRunning) {
    leap_->config_.setRunning(isRunning);
}

namespace {

void maxDelete(MaxStruct *max) {
    delete max->maxObject_;
}

void* maxNew(t_symbol *s, long argc, t_atom *argv) {
    MaxStruct* max = (MaxStruct*) object_alloc(CLASS_POINTER);
    if (max)
        max->maxObject_ = new MaxObject(max, s, argc, argv);
    return max;
}

void maxInt(MaxStruct *max, long n) {
    max->maxObject_->setRunning(n);
}

void bang(MaxStruct *max) {
    max->maxObject_->bang();
}

void start(MaxStruct *max) {
    max->maxObject_->setRunning(true);
}

void stop(MaxStruct *max) {
    max->maxObject_->setRunning(false);
}

void assist(MaxStruct *max, void *b, long m, long a, char *s) {
    auto message = (m == ASSIST_INLET) ?
            "bang, start, stop" : "leap data messages";
    sprintf(s, "%s %ld", message, a);
}

int j = 0;

t_max_err getHand(MaxStruct *max, void*, long *atomCount, t_atom **atoms) {
    print("getHand " + to_string(j++));
    if (!(atomCount && atoms))
        return MAX_ERR_NONE;

    auto hand = max->maxObject_->leap().config_.getHand();
    char alloc;
    if (auto err = atom_alloc_array(hand.size(), atomCount, atoms, &alloc))
        return err;

    for (auto i = 0; i < hand.size(); ++i) {
        print(to_string(i) + ": " + hand[i]);
        if (i < 0)
            setSymbol(atoms[i], hand[i]);
    }
    return MAX_ERR_NONE;
}

t_max_err setHand(MaxStruct *max, void *, long atomCount, t_atom *atoms) {
    post(("setHand " + to_string(atomCount)).c_str());

    Representation success, fail;
    for (auto atom = atoms; atom != atoms + atomCount; ++atom) {
        if (atom->a_type == A_SYM)
            success.emplace_back(getSymbol(atom));
        else if (atom->a_type == A_LONG)
            fail.emplace_back(to_string(atom_getlong(atom)));
        else if (atom->a_type == A_FLOAT)
            fail.emplace_back(to_string(atom_getfloat(atom)));
        else
            fail.emplace_back("unknown type " + to_string(atom->a_type));
    }

    auto& config = max->maxObject_->leap().config_;
    auto fail2 = config.setHand(success);
    fail.insert(fail.end(), fail2.begin(), fail2.end());

    if (!fail.empty()) {
        std::sort(fail.begin(), fail.end());
        config.logger_.err("Don't understand properties for attribute @hand");
        for (auto& f: fail)
            config.logger_.err(f);
    }

    config.setHand(success);
    return MAX_ERR_NONE;
}

}  // namespace

void registerMaxObject() {
    CLASS_POINTER = class_new("SwirlyLeap",
        (method) maxNew, (method) maxDelete,
        sizeof(MaxStruct), nullptr, A_GIMME, 0);
    auto sl = CLASS_POINTER;

    class_addmethod(sl, (method) assist, "assist", A_CANT, 0);
    class_addmethod(sl, (method) bang, "bang", 0);
    class_addmethod(sl, (method) start, "start", 0);
    class_addmethod(sl, (method) stop, "stop", 0);
    class_addmethod(sl, (method) maxInt, "int", A_LONG, 0);

    CLASS_ATTR_SYM_VARSIZE(
        sl, "hand", 0, MaxStruct, hands_, numHands_, MAX_PROPERTIES);
    CLASS_ATTR_ACCESSORS(sl, "hand", (method) getHand, (method) setHand);
#if 0
    CLASS_ATTR_ACCESSORS(sl, "finger", (method) getFinger, (method) setFinger);
    CLASS_ATTR_ACCESSORS(sl, "tool", (method) getTool, (method) setTool);
#endif

    class_register(CLASS_BOX, sl);
}

}  // namespace leap
}  // namespace swirly
