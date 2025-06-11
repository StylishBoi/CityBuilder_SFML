#ifndef BT_SELECTOR_H
#define BT_SELECTOR_H

#include "bt_composite.h"

namespace core::ai {
  namespace behaviour_tree {

    class Selector : public Composite {

    public:
      Status Tick() override;
    };
  }
}

#endif //BT_SELECTOR_H
