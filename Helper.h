/*** Types (variables) ***/
/** Statics (commons) **/ // static type;
static char SerialBuffer[1024];

/*** Classes (structures) ***/
/** Helpers (generic) **/
/*
 * Represents a timing device
 */
class Timeline {
  // Update frequency for the loop
  // [Unit] Millisecond [1 x 10^-3 s] {t}
  public: unsigned int Period;

  // Current time
  // [Unit] Millisecond [1 x 10^-3 s] {t}
  public: unsigned long CurrentTimer;

  // Last time since triggered
  // [Unit] Millisecond [1 x 10^-3 s] {t}
  public: unsigned long PreviousTimer;

  /*
   * Constructs a timer
   * [Input] unsigned int period - time for the timer to run at
   * [Output] Constructor
   */
  public: Timeline(unsigned int period) {
    unsigned long current = millis();

    // Set the period
    this->Period = period;

    // Set the timer as now
    this->CurrentTimer = current;

    // Set the last checkpoint as 0 (will still take time for the first iteration)
    this->PreviousTimer = 0;
  }

  /*
   * Updates the current timer
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void UpdateCurrentTimer() {
    unsigned long current = millis();

    // Update the current timer
    this->CurrentTimer = current;
  }
  
  /*
   * Updates the previous checkpoint
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void UpdatePreviousTimer() {
    unsigned long current = millis();

    // Update the previous checkpoint
    this->PreviousTimer = current;
  }

  /*
   * Synchronous wait to block execution until this is true
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void Wait() {
    // Update the timer for an initial check
    this->UpdateCurrentTimer();

    // Keep checking if we pass the time period
    while (this->CurrentTimer - this->PreviousTimer < this->Period) {
      this->UpdateCurrentTimer();
    }

    // Update the previous checkpoint
    this->UpdatePreviousTimer();
  }

  /*
   * [Input] void/nil
   * [Output] bool - if the time elapsed has been long enough
   * [Purpose] Asynchronous checks to run
   */
  public: bool IsReady() {
    // Update the timer for a check
    this->UpdateCurrentTimer();

    // Check if we passed the time period
    bool output = (this->CurrentTimer - this->PreviousTimer) > this->Period;
    
    // If so, update the previous checkpoint
    if (output == true) {
      this->UpdatePreviousTimer();
    }

    // Return the value
    return output;
  }
};



/*
 * Represents a system device
 */
class System {
  /*** Types (variables) ***/
  /** Triggers (conditions) **/ // bool;
  /** Loops (persistence) **/ // type;
  /** States (logic) **/ // enum _ {_ = _};
  /** Constants (invariants) **/ // const type;
  /** Statics (commons) **/ // static type;
  /** Timelines (schedule) **/ // Timeline





  /*** Delegates (functions) ***/
  /** Controllers (throughput) **/
  /** Actions (commands) **/
  /** Sequences (behaviors) **/
  /*
   * Main function
   * [Input] void/nil
   * [Output] void/nil
   * [Abstract]
   */
  public: virtual void Main() = 0;
  
  /*
   * Update function
   * [Input] void/nil
   * [Output] void/nil
   * [Abstract]
   */
  public: virtual void Update() = 0;
};
