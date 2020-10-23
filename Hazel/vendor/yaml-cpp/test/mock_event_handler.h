#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/eventhandler.h"
#include "yaml-cpp/mark.h"

#include "gmock/gmock.h"

#include <string>

namespace YAML {

class MockEventHandler : public EventHandler {
 public:
  MOCK_METHOD1(OnDocumentStart, void(const Mark&));
  MOCK_METHOD0(OnDocumentEnd, void());

  MOCK_METHOD2(OnNull, void(const Mark&, anchor_t));
  MOCK_METHOD2(OnAlias, void(const Mark&, anchor_t));
  MOCK_METHOD4(OnScalar, void(const Mark&, const std::string&, anchor_t,
                              const std::string&));

  MOCK_METHOD4(OnSequenceStart, void(const Mark&, const std::string&, anchor_t,
                                     EmitterStyle::value));
  MOCK_METHOD0(OnSequenceEnd, void());

  MOCK_METHOD4(OnMapStart, void(const Mark&, const std::string&, anchor_t,
                                EmitterStyle::value));
  MOCK_METHOD0(OnMapEnd, void());
  MOCK_METHOD2(OnAnchor, void(const Mark&, const std::string&));
};
}  // namespace YAML
