#ifndef AI_BT_NODE_H_
#define AI_BT_NODE_H_

namespace core::ai {
namespace behaviour_tree {

  //The status that all nodes will be following
    enum class Status {
      kSuccess,
      kFailure,
      kRunning
    };

    class Node {
      public:
      //Virtual means an action that will be redefined in a derived class
        virtual void Reset()=0;
        virtual Status Tick()=0;

      protected:
        Status status_=Status::kFailure;
    };
  }
}
#endif  // AI_BT_NODE_H_
