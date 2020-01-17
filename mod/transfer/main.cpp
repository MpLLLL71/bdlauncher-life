#include <Loader.h>
#include <MC.h>
#include "base.h"
#include "main.command.h"

extern "C" {
BDL_EXPORT void mod_init(std::list<string> &modlist);
}
extern void load_helper(std::list<string> &modlist);

void TransferCommand::invoke(mandatory<std::string> server, mandatory<int> port) {
  MyPkt trpk(0x55, [&](void *, BinaryStream &x) -> void {
    x.writeUnsignedVarInt(server.size());
    x.write(server.data(), server.size());
    x.writeUnsignedShort(port);
  });
  auto sp = getSP(getOrigin().getEntity());
  if (sp) {
    sp->sendNetworkPacket(trpk);
    getOutput().success();
  } else {
    getOutput().error("fucku");
  }
}

void mod_init(std::list<string> &modlist) {
  register_commands();
  do_log("loaded! V2019-12-14");
  load_helper(modlist);
}
