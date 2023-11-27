#ifndef _ANIMATION_
#define _ANIMATION_

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Animation
		{
			enum AnimationTypes
			{
				Idle,
				Walk,
				Run,
				Jump,
				Max
			};

			class Animation
			{
			public:

				Animation();

			private:
				//Does the animation hold the reference to the texture??
			};
		}
	}
}

#endif