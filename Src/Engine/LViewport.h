#pragma once
#include "pre.h"

#include <QOpenGLWidget>

namespace Lumin
{
	class LEngine;
	struct ENGINE_API LViewportConfig
	{
		int width;
		int height;
		LEngine* engine;
	};

	class ENGINE_API LViewport : public QOpenGLWidget/*, protected QOpenGLFunctions_3_3_Core*/
	{
		Q_OBJECT
	public:
		explicit LViewport(const LViewportConfig& config, QWidget* parent = nullptr);
		~LViewport() override;
		bool ViewportShouldClose() const;
	protected:
		void initializeGL() override;
		void resizeGL(int w, int h) override;
		void paintGL() override;
		void keyPressEvent(QKeyEvent* event) override;
		void keyReleaseEvent(QKeyEvent* event) override;
		void mouseMoveEvent(QMouseEvent* event) override;
		void mousePressEvent(QMouseEvent* event) override;
		void mouseReleaseEvent(QMouseEvent* event) override;
		void closeEvent(QCloseEvent* event) override;
	private:
		bool m_canShow = true;
		LEngine* m_engine;
	};


}
