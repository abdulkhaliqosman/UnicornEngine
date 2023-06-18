
namespace uniengine
{
    enum class EngineStates
    {
        Uninitialized,
        Stopped,
        Playing,
        Paused,
        Shutdown
    }

    // Uninitialized -> Initialize() -> Stopped -> Shutdown() -> Shutdown
    //                                   V   ^
    //                              Start() Stop()
    //                                   V   ^
    //                                  Playing
    //                                   V   ^
    //                              Pause() Resume()
    //                                   V   ^
    //                                  Paused

    // fake SM
    class EngineStateMachine
    {
    public:
        
        void Initialize();
        void Start();
        void Pause();
        void Resume();
        void Stop();
        void Shutdown();

        inline EngineStates GetCurrentState() { return m_CurrentState; }
        inline EngineStates GetNextState() { return m_NextState; }
    private:
        EngineStates m_CurrentState = EngineStates::Uninitialized;
        EngineStates m_NextState = EngineStates::Uninitialized;
    };
}