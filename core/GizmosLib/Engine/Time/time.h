#ifndef  _TIME_
#define _TIME_

namespace GizmosLIb
{
	namespace Engine
	{
		namespace Core
		{
			class Time
			{
			public:
				static Time* Instance;

				Time();

				void Update();

				float GetTime();

				float GetDeltaTime();

			private:
				void initialize();

				float _time;
				float _deltaTime;

				float _prevFrameTime;
			};
		}
	}
}

#endif 
