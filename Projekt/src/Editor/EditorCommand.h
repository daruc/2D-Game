#ifndef EDITOR_COMMAND_H
#define EDITOR_COMMAND_H

class EditorCommand
{
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual ~EditorCommand() = default;
};

#endif