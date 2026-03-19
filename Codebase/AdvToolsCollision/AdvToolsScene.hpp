#ifndef ADVTOOLSSCENE_HPP
#define ADVTOOLSSCENE_HPP



#include "mge/core/AbstractGame.hpp"
#include "CollisionManager.hpp"

class DebugHud;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class AdvToolsScene : public AbstractGame
{
	//PUBLIC FUNCTIONS

	public:
		AdvToolsScene();
		virtual ~AdvToolsScene();

		//override initialize so we can add a DebugHud
		virtual void initialize();

	protected:
		//override so we can construct the actual scene
		virtual void _initializeScene();

		//override render to render the hud as well.
		virtual void _render();

	private:
		DebugHud* _hud;                   //hud display
		CollisionManager* _collisionManager;

		void _updateHud();

		AdvToolsScene(const AdvToolsScene&);
		AdvToolsScene& operator=(const AdvToolsScene&);
};






#endif // ADVTOOLSSCENE_HPP
