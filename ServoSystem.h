/*** Classes (structures) ***/
/** Systems (modules) **/
/*
 * Represents a servo motor
 */
class ServoSystem : public System {
  /*** Types (variables) ***/
  /** Triggers (conditions) **/ // bool;
  public: bool PositionControlPeriodReached;
  public: bool PlanControlPeriodReached;
  public: bool SwingPeriodReached;


  
  /** Loops (persistence) **/ // type;
  public: Servo ServoMotor;
  public: int Port;
  public: int TargetPosition = 0;
  // [Todo] Use inheritance instead
  public: enum ServoType {
    LeftShoulder = 0,
    RightShoulder = 1,
    Arm = 2,
    Elbow = 3,
    Wrist = 4
  };
  public: ServoType ShoulderState;


  
  /** States (logic) **/ // enum _ {_ = _};
  public: enum ShoulderState {
    ShoulderLock = 0,
    ShoulderPivot = 1
  };
  public: ShoulderState ShoulderState;
  
  public: enum ArmState {
    ArmUp = 0,
    ArmDown = 1
  };
  public: ArmState ArmState;
  
  public: enum ElbowState {
    ElbowUp = 0,
    ElbowDown = 1
  };
  public: ElbowState ElbowState;
  
  public: enum WristState {
    WristReady = 0,
    Flick = 1
  };


  
  /** Constants (invariants) **/ // const type;
  /** Statics (commons) **/ // static type;
  /** Timelines (schedule) **/ // Timeline  
  // Position control schedule
  public: Timeline PositionControlTimeline;
  
  // Plan control schedule
  public: Timeline PlanControlTimeline;

  // Swing timer
  public: Timeline SwingTImeline;


  
  
  
  /*** Delegates (functions) ***/
  /*
   * Constructs a servo controller
   * [Input] unsigned int period - sets the period
   * [Output] Constructor
   */
  public: ServoSystem(unsigned int port, ServoType type) : PositionControlTimeline(15), PlanControlTimeline(15), SwingTimeline(15) {
    this->Port = port;
    this->State = RightGo;
    this->PositionControlPeriodReached = false;
    this->PlanControlPeriodReached = false;
    this->SwingPeriodReached = false;
    this->TargetPosition = 0;
    this->Type = type;
  }
  
  
  
  /** Controllers (throughput) **/
  /*
   * Checks timing
   * [Input] void/nil
   * [Output] void/nil
   */
  void TimeController() {
    this->SweepDelayReached = false;
    if (this->SweepTimeline.IsReady()) {
      this->SweepDelayReached = true;
    }

    this->PositionControlPeriodReached = false;
    if (this->PositionControlTimeline.IsReady()) {
      this->PositionControlPeriodReached = true;
    }
    
    this->PlanControlPeriodReached = false;
    if (this->PlanControlTimeline.IsReady()) {
      this->PlanControlPeriodReached = true;
    }
  }


  
  /*
   * Sweeps
   * [Input] void/nil
   * [Output] void/nil
   */
  void SweepController() {
    switch (this->State) {
      case LeftGo:
        Serial.println("[Servo %s] Going left");
        /* Events -> Triggers */
        if (this->MinReached == true) {
          Serial.println("[Servo Sweeper] Triggered left pause");
          this->ResetSweepTimer();
          this->State = LeftPause;
        }
        break;
      case LeftPause:
        Serial.println("[Servo Sweeper] Pausing left");
        /* Events -> Triggers */
        if (this->SweepDelayReached == true) {
          Serial.println("[Servo Sweeper] Triggered right go");
          // this->GoRight();
          this->State = RightGo;
        }
        break;
      case RightGo:
        Serial.println("[Servo Sweeper] Going right");
        /* Events -> Triggers */
        if (this->MaxReached == true) {
          Serial.println("[Servo Sweeper] Triggered right pause");
          this->ResetSweepTimer();
          this->State = RightPause;
        }
        break;
      case RightPause:
        Serial.println("[Servo Sweeper] Pausing right");
        /* Events -> Triggers */
        if (this->SweepDelayReached == true) {
          Serial.println("[Servo Sweeper] Triggered left go");
          this->State = LeftGo;
        }
        break;
    }
  }



  /*
   * Sets position
   * [Input] void/nil
   * [Output] void/nil
   */
  void PositionController() {
    this->MinReached = false;
    this->MaxReached = false;
    if (this->PositionControlPeriodReached == true) {
//      switch (this->State) {
//        case LeftGo:
//          this->TargetPosition -= 1;
//          /* Events -> Triggers */
//          if (this->TargetPosition <= 0) {
//            this->MinReached = true;
//            this->TargetPosition = 0;
//          }
//          break;
//        case LeftPause:
//          this->TargetPosition -= 0;
//          break;
//        case RightGo:
//          this->TargetPosition += 1;
//          /* Events -> Triggers */
//          if (this->TargetPosition >= 180 ) {
//            this->MaxReached = true;
//            this->TargetPosition = 180;
//          }
//          break;
//        case RightPause:
//          this->TargetPosition += 0;
//          break;
//      }
  
      sprintf(SerialBuffer, "[Servo %d] Going to %d\n", this->Port, this->TargetPosition);
      Serial.print(SerialBuffer);
      
      this->ServoMotor.write(this->TargetPosition);
    }
  }

  /*
   * Sets position
   * [Input] void/nil
   * [Output] void/nil
   */
  void PlanController() {
    if (this->PlanControlPeriodReached == true) {
      this->TargetPosition += this->Port;
      this->TargetPosition = this->TargetPosition % 180;
    }
  }
  

  
  /** Actions (commands) **/
  /*
   * Print for the on state
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void ResetSweepTimer() {
    this->SweepTimeline.UpdateCurrentTimer();
    this->SweepTimeline.UpdatePreviousTimer();
  }
  

  
  /** Sequences (behaviors) **/  
  /*
   * Main function
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void Main() {
    this->ServoMotor.attach(this->Port);
  }
  
  /*
   * Update function
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void Update() {
    this->TimeController();
    this->PositionController();
    this->PlanController();
  }
};
