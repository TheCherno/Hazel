#pragma once

#include <gtkmm.h>
#include <gtkmm/application.h>

namespace Hazel {

  class LinuxDialogWindow : public Gtk::Window
  {
  public:
    LinuxDialogWindow(void);
    virtual ~LinuxDialogWindow(void) override;
    std::string GetFileName(void) const { return m_ChosenFile; }
    void SubmitHazelFilter(const char* filter);

  protected:
    // Signal handlers
    void OnFileButtonClicked(void);

  private:
    std::string m_ChosenFile;
    std::string m_HZFilterName;
    std::string m_HZFilterPattern;
  };

}
