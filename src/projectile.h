#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "rectangle.h"
#include "units.h"

struct Projectile {
   virtual Rectangle getCollisionRectangle() const = 0;
   virtual units::HP getContactDamage() const = 0;
};

#endif /* PROJECTILE_H_ */

