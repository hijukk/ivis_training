#include <iostream>

class Document;

class Invoker
{
public:
    Invoker(Command* pCommand, Command* oCommand);

    void run();
private:
    Command* pasteCommand;
    Command* openCommand;
};

class Command
{
public:
    virtual ~Command();

    virtual void execute() = 0;

protected:
    Command();
};

class PasteCommand : public Command
{
public:
    PasteCommand(Document* d);

    void execute();

private:
    Document* document;
};

class OpenCommand : public Command
{
public:
    OpenCommand(Document* d);

    void execute();

private:
    Document* document;
};

class Document
{
public:
    void open()
    {
        std::cout << "open.." << std::endl;
    }
    void close()
    {
        std::cout << "close.." << std::endl;
    }
    
    void cut()
    {
        std::cout << "cut.." << std::endl;
    }
    
    void copy()
    {
        std::cout << "copy.." << std::endl;
    }
    
    void paste()
    {
        std::cout << "paste.." << std::endl;
    }
};


Invoker::Invoker(Command* pCommand, Command* oCommand)
{
    pasteCommand = pCommand;
    openCommand = oCommand;
}

void Invoker::run()
{
    pasteCommand->execute();
    openCommand->execute();
}

PasteCommand::PasteCommand(Document* d)
{
    document = d;
}

void PasteCommand::execute()
{
    document->paste();
}

OpenCommand::OpenCommand(Document* d)
{
    document = d;
}

void OpenCommand::execute()
{
    document->open();
}

