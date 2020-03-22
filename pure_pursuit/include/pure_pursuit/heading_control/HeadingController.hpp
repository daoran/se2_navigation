/*
 * HeadingController.hpp
 *
 *  Created on: Mar 21, 2020
 *      Author: jelavice
 */

#pragma once
#include "pure_pursuit/Path.hpp"
#include "pure_pursuit/common.hpp"

namespace pure_pursuit {

struct HeadingControllerParameters {
  virtual ~HeadingControllerParameters() = default;
  double lookaheadDistanceFwd_ = 4.0;
  double lookaheadDistanceBck_ = 4.0;
  double anchorDistanceFwd_ = 0.2;
  double anchorDistanceBck_ = 0.2;
};

class HeadingController {
 public:
  HeadingController() = default;
  virtual ~HeadingController() = default;

  bool initialize(double dt);
  bool advance(double dt);
  virtual void updateCurrentPathSegment(const PathSegment& pathSegment);
  virtual void updateCurrentState(const RobotState& robState);
  double getTurningRadius() const;
  double getYawRate() const;
  double getSteeringAngle() const;

 private:
  virtual bool advanceImpl(double dt) = 0;
  virtual bool initializeImpl(double dt) = 0;
  virtual void setActiveAnchorAndLookaheadDistance();
  virtual bool computeYawRate(double dt) = 0;
  virtual bool computeTurningRadius(double dt) = 0;
  virtual bool computeSteeringAngle(double dt) = 0;

 protected:
  RobotState currentRobotState_;
  double turningRadius_ = 0.0;
  double yawRate_ = 0.0;
  double steeringAngle_ = 0.0;
  HeadingControllerParameters parameters_;
  double activeAnchorDistance_ = 0.2;
  double activeLookaheadDistance_ = 0.2;
  PathSegment currentPathSegment_;
  unsigned int lastClosesPointId_ = 0.0;
};

}  // namespace pure_pursuit
