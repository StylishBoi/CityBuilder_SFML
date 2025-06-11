#include "../../include/ai/bt_sequence.h"

using namespace core::ai::behaviour_tree;


Status Sequence::Tick() {

  while (childIdx_<children_.size()) {
    Status status = children_[childIdx_]->Tick();

    switch (status) {
      case Status::kFailure:
        Reset();
        return Status::kFailure;

      case Status::kRunning:
        return Status::kRunning;

      default:
        childIdx_++;
    }
  }
  Reset();
  return Status::kSuccess;
}