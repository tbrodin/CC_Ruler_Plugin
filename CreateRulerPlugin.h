#pragma once

#include "ccStdPluginInterface.h"
#include "qdialog.h"
#include <QtGui>
#include "qdialog.h"
#include "qlayout.h"
#include "qformlayout.h" 
#include "qpushbutton.h"
#include "ccPlane.h"
#include "qlineedit.h"
#include "qlabel.h"
#include "qdialogbuttonbox.h"
#include "qstring.h"

//! Example qCC plugin
/** Replace 'ExamplePlugin' by your own plugin class name throughout and then
	check 'ExamplePlugin.cpp' for more directions.

	Each plugin requires an info.json file to provide information about itself -
	the name, authors, maintainers, icon, etc..

	The one method you are required to implement is 'getActions'. This should
	return all actions (QAction objects) for the plugin. CloudCompare will
	automatically add these with their icons in the plugin toolbar and to the
	plugin menu. If	your plugin returns	several actions, CC will create a
	dedicated toolbar and a	sub-menu for your plugin. You are responsible for
	connecting these actions to	methods in your plugin.

	Use the ccStdPluginInterface::m_app variable for access to most of the CC
	components (database, 3D views, console, etc.) - see the ccMainAppInterface
	class in ccMainAppInterface.h.
**/
class CreateRulerPlugin : public QObject, public ccStdPluginInterface
{
	Q_OBJECT
	Q_INTERFACES( ccStdPluginInterface )

	// Replace "Example" by your plugin name (IID should be unique - let's hope your plugin name is unique ;)
	// The info.json file provides information about the plugin to the loading system and
	// it is displayed in the plugin information dialog.
	Q_PLUGIN_METADATA( IID "cccorp.cloudcompare.plugin.CreateRuler" FILE "info.json" )

public:
	explicit CreateRulerPlugin( QObject *parent = nullptr );
	~CreateRulerPlugin() override = default;

	// Inherited from ccStdPluginInterface
	void onNewSelection( const ccHObject::Container &selectedEntities ) override;
	QList<QAction *> getActions() override;

private:
	void performActionCreateRuler();
	//! Default action
	/** You can add as many actions as you want in a plugin.
		Each action will correspond to an icon in the dedicated
		toolbar and an entry in the plugin menu.
	**/
	QAction* m_action;
};
