#ifndef BT_NODE_H
#define BT_NODE_H

namespace core::ai{
  namespace behaviour_tree {

    enum class Status {
      kSuccess,
      kFailure,
      kRunning
    };

    class Node {
      public:
        virtual void Reset()=0;
        virtual Status Tick()=0;

      protected:
        Status status_=Status::kFailure;
    };
  }
}
#endif //BT_NODE_H
