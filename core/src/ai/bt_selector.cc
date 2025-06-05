#include "ai/bt_selector.h"

using namespace core::ai::behaviour_tree;

void Selector::AddChild(std::unique_ptr<Node> child){
  children_.push_back(std::move(child));
}

void Selector::Reset() {
  childIdx_=0;
}

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
}