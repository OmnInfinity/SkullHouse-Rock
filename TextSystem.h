/*** Classes (structures) ***/
/** Systems (modules) **/
/*
 * Represents a text blinker
 */
class TextSystem : public System {
  /*** Types (variables) ***/
  /** Triggers (conditions) **/ // bool;
  public: bool PeriodReached;


  
  /** Loops (persistence) **/ // type;
  public: char* String1;
  public: char* String2;


  
  /** States (logic) **/ // enum _ {_ = _};
  public: enum BlinkState {
    Odd = 0,
    Even = 1
  };
  public: BlinkState State;


  
  /** Constants (invariants) **/ // const type;
  /** Statics (commons) **/ // static type;
  /** Timelines (schedule) **/ // Timeline
  // Text blink schedule
  public: Timeline TextTimeline;


  
  
  
  /*** Delegates (functions) ***/
  /*
   * Constructs a text blinker
   * [Input] unsigned int period - sets the period
   * [Output] Constructor
   */
  public: TextSystem(unsigned int period, char* string1, char* string2) : TextTimeline(period) {
    this->State = Odd;
    this->PeriodReached = false;
    this->String1 = string1;
    this->String2 = string2;
  }
  

  
  /** Controllers (throughput) **/
  /*
   * Checks timing
   * [Input] void/nil
   * [Output] void/nil
   */
  void TimeController() {
    this->PeriodReached = false;
    if (this->TextTimeline.IsReady()) {
      this->PeriodReached = true;
    }
  }


  
  /*
   * Blinks
   * [Input] void/nil
   * [Output] void/nil
   */
  void BlinkController() {
    switch (this->State) {
      case Odd:
        // Serial.println("[Text Blinker] Odd");
        /* Events -> Triggers */
        if (PeriodReached == true) {
          // Serial.println("[Text Blinker] Triggered even");
          this->DisplayEven();
          this->State = Even;
        }
        break;
        
      case Even:
        // Serial.println("[Text Blinker] Even");
        /* Events -> Triggers */
        if (PeriodReached == true) {
          // Serial.println("[Text Blinker] Triggered odd");
          this->DisplayOdd();
          this->State = Odd;
        }
        break;
    }
  }


  
  /** Actions (commands) **/
  /*
   * Print for the on state
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void DisplayOdd() {
    sprintf(SerialBuffer, "[Text Blinker] %s\n", this->String1);
    Serial.print(SerialBuffer);
  }

  /*
   * Print for the off state
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void DisplayEven() {
    sprintf(SerialBuffer, "[Text Blinker] %s\n", this->String2);
    Serial.print(SerialBuffer);
  }
  

  
  /** Sequences (behaviors) **/  
  /*
   * Main function
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void Main() { }
  
  /*
   * Update function
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void Update() {
    this->TimeController();
    this->BlinkController();
  }
};
