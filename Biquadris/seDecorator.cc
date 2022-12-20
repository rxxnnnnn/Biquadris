#include "seDecorator.h"
#include "SpecialEffect.h"
using namespace std;


//constructor of seDecorator
seDecorator::seDecorator(shared_ptr<SpecialEffect> se):se{se}{}


//destructor of seDecorator
seDecorator::~seDecorator(){}
