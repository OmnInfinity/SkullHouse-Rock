/*** Classes (structures) ***/
/** Systems (modules) **/
/*
 * Represents the processor
 */
 class ProcessorSystem : public System {
  /*** Types (variables) ***/
  /** Triggers (conditions) **/ // bool;
  /** Loops (persistence) **/ // type;
  /** States (logic) **/ // enum _ {_ = _};
  /** Constants (invariants) **/ // const type;
  /** Statics (commons) **/ // static type;
  /** Timelines (schedule) **/ // Timeline
  // Update loop schedule
  public: Timeline UpdateTimeline;


  
  
  
  /*** Delegates (functions) ***/
  /*
   * Constructs a processor
   * [Input] void/nil
   * [Output] Constructor
   */
  public: ProcessorSystem() : UpdateTimeline(20) { }
  

  
  /** Controllers (throughput) **/
  /** Actions (commands) **/
  /*
   * Sets up the pinout I/O
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void PinoutSetup() {
    // [Configuration] Pinout
    // pinMode(InternalClockDisplayModeButton, INPUT_PULLUP);
    
  }
  
  /*
   * Sets up the serial communications with a computer
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void SerialSetup() {
    // Set up the serial port at 115200 baud and wait for it to initialize
    Serial.begin(115200);
    delay(100);

    // Set up the bus and wait for it to initialize
    Wire.begin();
    delay(50);
  }

  /*
   * Sets up all hardware-related systems
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void HardwareSetup() {
    // [Alternative] Make each one load themselves
    PinoutSetup();
    SerialSetup();
  }

  // [Deprecated]
  /*
   * Sets up all software-related systems
   * [Input] void/nil
   * [Output] void/nil
   */
   public: void SoftwareSetup() { }
  
  // [Todo]
   public: void UsbSetup() { }


  
  /** Sequences (behaviors) **/  
  /*
   * Main function
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void Main() {
    this->SerialSetup();
  }
  
  /*
   * Update function
   * [Input] void/nil
   * [Output] void/nil
   */
  public: void Update() {
    this->UpdateTimeline.Wait();
  }
};
