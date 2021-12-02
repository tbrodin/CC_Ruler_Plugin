//##########################################################################
//#                                                                        #
//#                CLOUDCOMPARE PLUGIN: TimPlugin (Simple Ruler            #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#                             COPYRIGHT: Tim Brodin                      #
//#                                                                        #
//##########################################################################

// First:
//	Replace all occurrences of 'ExamplePlugin' by your own plugin class name in this file.
//	This includes the resource path to info.json in the constructor.

// Second:
//	Open ExamplePlugin.qrc, change the "prefix" and the icon filename for your plugin.
//	Change the name of the file to <yourPluginName>.qrc

// Third:
//	Open the info.json file and fill in the information about the plugin.
//	 "type" should be one of: "Standard", "GL", or "I/O" (required)
//	 "name" is the name of the plugin (required)
//	 "icon" is the Qt resource path to the plugin's icon (from the .qrc file)
//	 "description" is used as a tootip if the plugin has actions and is displayed in the plugin dialog
//	 "authors", "maintainers", and "references" show up in the plugin dialog as well

#include <QtGui>
#include "CreateRulerPlugin.h"
#include <iostream>


// Default constructor:
//	- pass the Qt resource path to the info.json file (from <yourPluginName>.qrc file) 
//  - constructor should mainly be used to initialize actions and other members
CreateRulerPlugin::CreateRulerPlugin( QObject *parent )
	: QObject( parent )
	, ccStdPluginInterface( ":/CC/plugin/CreateRulerPlugin/info.json" )
	, m_action( nullptr )
{
}

// This method should enable or disable your plugin actions
// depending on the currently selected entities ('selectedEntities').
void CreateRulerPlugin::onNewSelection( const ccHObject::Container &selectedEntities )
{
	if ( m_action == nullptr )
	{
		return;
	}
	
}

// This method returns all the 'actions' your plugin can perform.
// getActions() will be called only once, when plugin is loaded.
QList<QAction *> CreateRulerPlugin::getActions()
{
	// default action (if it has not been already created, this is the moment to do it)
	if ( !m_action )
	{
		// Here we use the default plugin name, description, and icon,
		// but each action should have its own.
		m_action = new QAction( getName(), this );
		m_action->setToolTip( getDescription() );
		m_action->setIcon( getIcon() );
		
		// Connect appropriate signal
		connect(m_action, &QAction::triggered, this, &CreateRulerPlugin::performActionCreateRuler);
	}

	return { m_action };
}

	// This is an example of an action's method called when the corresponding action
	// is triggered (i.e. the corresponding icon or menu entry is clicked in CC's
	// main interface). You can access most of CC's components (database,
	// 3D views, console, etc.) via the 'appInterface' variable.
void CreateRulerPlugin::performActionCreateRuler()
	{
		if (m_app == nullptr )
		{
			// The application interface should have already been initialized when the plugin is loaded
			Q_ASSERT( false );
			
			return;
		}
		
		/*** HERE STARTS THE ACTION ***/
		
		QDialog rulerDlg;
		rulerDlg.setWindowTitle("Simple Ruler Creator");
		QFormLayout rulerDlgLayout(&rulerDlg);
			
		QString dlgLengthLabel("Ruler length");
		QLineEdit* lineEditSegmentLength = new QLineEdit();

		QString dlgWidthLabel("Ruler Width");
		QLineEdit* lineEditSegmentWidth = new QLineEdit();

		QString dlgNrOfSegmentsLabel("Numer of segments");		
		QLineEdit* lineEditNrSegments = new QLineEdit();

		rulerDlgLayout.addRow(dlgLengthLabel, lineEditSegmentLength);
		rulerDlgLayout.addRow(dlgWidthLabel, lineEditSegmentWidth);

		//appInterface->dispToConsole("stupid debug 1", ccMainAppInterface::ERR_CONSOLE_MESSAGE);
		
		rulerDlgLayout.addRow(dlgNrOfSegmentsLabel, lineEditNrSegments);

		// Add some standard buttons (Cancel/Ok) at the bottom of the dialog
		QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
			Qt::Horizontal, &rulerDlg);

		rulerDlgLayout.addRow(&buttonBox);

		QObject::connect(&buttonBox, SIGNAL(accepted()), &rulerDlg, SLOT(accept()));
		QObject::connect(&buttonBox, SIGNAL(rejected()), &rulerDlg, SLOT(reject()));

		int rulerLength;
		int rulerWidth;
		int rulerNoOfSegments;

		
		// Show the dialog as modal
		if (rulerDlg.exec() == QDialog::Accepted) {
			// If the user didn't dismiss the dialog, do something with the fields
			rulerLength = lineEditSegmentLength->text().toInt();
			rulerWidth = lineEditSegmentWidth->text().toInt();
			rulerNoOfSegments = lineEditNrSegments->text().toInt();

			ccPlane* rulerContainer = new ccPlane("Ruler");
			
			int segmentOffset;

			for (int i = 0; i < rulerNoOfSegments; i++) {
				segmentOffset = i * rulerLength / rulerNoOfSegments;

				ccGLMatrix* trans = new ccGLMatrix();
				trans->setColumn(3, CCVector3(segmentOffset, 0, 0));

				ccGenericPrimitive* segment = new ccPlane(rulerLength/rulerNoOfSegments, rulerWidth, trans, QString("ruler segment_%1").arg(i + 1));
				
				if (i % 2) {
					segment->setColor(ccColor::darkBlue);
				}
				else {
					segment->setColor(ccColor::white);
				}
				
				segment->showColors(true);
				rulerContainer->merge(segment, false);
			}

			m_app->addToDB(rulerContainer);
			//setCameratoTopView 
			//ccViewportParameters* view = new ccViewportParameters();
			//view->perspectiveView = false;
			//view->objectCenteredView = true;
		}

	}