#include "action.hh"

// constructor
MyActionInitialization::MyActionInitialization() {

}

// destructor
MyActionInitialization::~MyActionInitialization() {

}

void MyActionInitialization::Build() const {
	MyPrimaryGenerator *generator = new MyPrimaryGenerator();
	SetUserAction(generator);
}
