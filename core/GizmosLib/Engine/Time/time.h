#ifndef  _TIME_
#define _TIME_

namespace GizmosLib
{
	namespace Engine
	{
		namespace Core
		{
			class Time
			{
			public:
				

				static void Update();

				static float GetTime();

				static float GetDeltaTime();

			private:
				Time();

				static float _time;
				static float _deltaTime;

				static float _prevFrameTime;
			};
		}
	}
}

#endif 
