#pragma once

namespace Lumin
{
	class LGameInstanceBase
	{
	public:
		virtual bool Init() = 0;
		virtual void Tick(float deltaTime = 0) = 0;// deltaTime is in seconds
		virtual void Destroy() = 0;

		void SetNeedToBeClosed(bool value);
		bool IsNeedToBeClosed() const;
	private:
		bool m_needToBeClosed;
	};
}


