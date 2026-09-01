#include "CommandDictionary.h"

#include "CmdDrawPixel.h"
#include "CmdSetResolution.h"
#include "CmdVarFloat.h"
#include "CmdVarInt.h"
#include "CmdVarBool.h"
#include "CmdSetColor.h"
#include "CmdBeginDraw.h"
#include "CmdEndDraw.h"
#include "CmdVertex.h"
#include "CmdSetFilledMode.h"
#include "CmdSetViewport.h"
#include "CmdSetClipping.h"
#include "CmdMatrixStack.h"
#include "CmdCamera.h"
#include "CmdSetCullMode.h"
#include "CmdSetShadeMode.h"
#include "CmdEnableDepth.h"
#include "CmdMaterial.h"
#include "CmdLights.h"
#include "CmdModel.h"
#include "CmdSetTexture.h"
#include "CmdSetCorrectUV.h"
#include "CmdSetUseFilter.h"
#include "CmdSetAddressMode.h"


CommandDictionary* CommandDictionary::Get()
{
	static CommandDictionary sInstance;
	return &sInstance;
}

CommandDictionary::CommandDictionary()
{
	// Initialize dictionary

	// Setting commands
	RegisterCommand<CmdSetResolution>();
	RegisterCommand<CmdSetViewport>();
	RegisterCommand<CmdSetClipping>();

	// Variable commands
	RegisterCommand<CmdVarFloat>();
	RegisterCommand<CmdVarInt>();
	RegisterCommand<CmdVarBool>();
	
	// Rasterization commands
	RegisterCommand<CmdDrawPixel>();
	RegisterCommand<CmdSetColor>();
	RegisterCommand<CmdSetFilledMode>();
	RegisterCommand<CmdEnableDepth>();
	RegisterCommand<CmdSetShadeMode>();
	RegisterCommand<CmdSetTexture>();
	RegisterCommand<CmdSetUseFilter>();
	RegisterCommand<CmdSetAddressMode>();

	// Material commands
	RegisterCommand<CmdSetMaterialEmissive>();
	RegisterCommand<CmdSetMaterialAmbient>();
	RegisterCommand<CmdSetMaterialDiffuse>();
	RegisterCommand<CmdSetMaterialSpecular>();
	RegisterCommand<CmdSetMaterialShininess>();

	// Light commands
	RegisterCommand<CmdSetLightAmbient>();
	RegisterCommand<CmdSetLightDiffuse>();
	RegisterCommand<CmdSetLightSpecular>();
	RegisterCommand<CmdAddDirectionalLight>();
	RegisterCommand<CmdAddPointLight>();
	RegisterCommand<CmdAddSpotLight>();

	// Primitive drawing commands
	RegisterCommand<CmdBeginDraw>();
	RegisterCommand<CmdVertex>();
	RegisterCommand<CmdEndDraw>();
	RegisterCommand<CmdSetCullMode>();
	RegisterCommand<CmdModel>();
	RegisterCommand<CmdSetCorrectUV>();

	//Matrix stack commands
	RegisterCommand<CmdPushTranslation>();
	RegisterCommand<CmdPushRotationX>();
	RegisterCommand<CmdPushRotationY>();
	RegisterCommand<CmdPushRotationZ>();
	RegisterCommand<CmdPushScaling>();
	RegisterCommand<CmdPopMatrix>();

	//Camera commands
	RegisterCommand<CmdSetCameraPosition>();
	RegisterCommand<CmdSetCameraDirection>();
	RegisterCommand<CmdSetCameraNear>();
	RegisterCommand<CmdSetCameraFar>();
	RegisterCommand<CmdSetCameraFOV>();	
}

TextEditor::LanguageDefinition CommandDictionary::GenerateLanguageDefinition()
{
	TextEditor::LanguageDefinition langDef;

	langDef.mName = "Pix";

	langDef.mKeywords.insert("var");

	for (auto& [keyword, command] : mCommandMap)
	{
		TextEditor::Identifier id;
		id.mDeclaration = command->GetDescription();
		langDef.mIdentifiers.insert(std::make_pair(keyword, id));
	}

	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\$[a-zA-Z_]+", TextEditor::PaletteIndex::Keyword));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("L?\\\"(\\\\.|[^\\\"])*\\\"", TextEditor::PaletteIndex::String));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\'\\\\?[^\\']\\'", TextEditor::PaletteIndex::CharLiteral));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", TextEditor::PaletteIndex::Number));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", TextEditor::PaletteIndex::Identifier));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[\\[\\]\\{\\}\\!\\%\\^\\&\\*\\(\\)\\-\\+\\=\\~\\|\\<\\>\\?\\/\\;\\,\\.]", TextEditor::PaletteIndex::Punctuation));

	langDef.mCommentStart = "/*";
	langDef.mCommentEnd = "*/";
	langDef.mSingleLineComment = "//";

	langDef.mAutoIndentation = true;
	langDef.mCaseSensitive = true;

	return langDef;
}

Command* CommandDictionary::CommandLookup(const std::string& keyword)
{
	auto iter = mCommandMap.find(keyword);
	if (iter == mCommandMap.end())
		return nullptr;
	return iter->second.get();
}

template <class T>
void CommandDictionary::RegisterCommand()
{
	static_assert(std::is_base_of_v<Command, T>, "Invalid command type.");
	auto newCommand = std::make_unique<T>();
	mCommandMap.emplace(newCommand->GetName(), std::move(newCommand));
}
