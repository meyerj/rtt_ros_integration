//=================================================================================================
// Copyright (c) 2012, Johannes Meyer, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Flight Systems and Automatic Control group,
//       TU Darmstadt, nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

#ifndef _ROS_SPIN_ACTIVITY_HPP_
#define _ROS_SPIN_ACTIVITY_HPP_

#include <rtt/Activity.hpp>
#include <boost/shared_ptr.hpp>
#include <rtt/Logger.hpp>

#include <ros/ros.h>
#include <ros/callback_queue.h>

namespace ros_integration{
    /**
     * A process wide thread that handles all publishing of
     * ROS topics of the current process.
     * There is no strong reason why only one publisher should
     * exist, in later implementations, one publisher thread per
     * channel may exist as well. See the usage recommendations
     * for Instance()
     */
  class RosSpinActivity : public RTT::Activity {
  public:
      typedef boost::shared_ptr<RosSpinActivity> shared_ptr;

  private:
      typedef boost::weak_ptr<RosSpinActivity> weak_ptr;
      //! This pointer may not be refcounted since it would prevent cleanup.
      static weak_ptr ros_spin_act;

      ros::CallbackQueuePtr queue;
      bool stopping;

      RosSpinActivity(const std::string& name);

      void loop();
      bool breakLoop();

  public:

      /**
       * Returns the single instance of the RosPublisher. This function
       * is not thread-safe when it creates the RosPublisher object.
       * Therefor, it is advised to cache the object which Intance() returns
       * such that, in the unlikely event that two publishers exist,
       * you consistently keep using the same instance, which is fine then.
       */
      static shared_ptr Instance();
      ~RosSpinActivity();

      ros::CallbackQueue* getCallbackQueue();

  };//class
}//namespace

#endif // ROS_SPIN_ACTIVITY_H
