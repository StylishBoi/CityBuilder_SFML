#include "../../include/ai/bt_selector.h"

using namespace core::ai::behaviour_tree;

//Tries the children in order until one succeeds
Status Selector::Tick() {

  while (childIdx_<children_.size()) {
    Status status = children_[childIdx_]->Tick();

    switch (status) {
      case Status::kSuccess:
        Reset();
        return Status::kSuccess;

      case Status::kRunning:
        return Status::kRunning;

      default:
        childIdx_++;
    }
  }
  return Status::kFailure;
}