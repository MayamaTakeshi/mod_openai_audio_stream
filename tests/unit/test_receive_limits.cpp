#include "test_support.h"
#include <ixwebsocket/IXWebSocketPerMessageDeflateCodec.h>

int main() {
    return run_test("bounded decompression", [] {
        ix::WebSocketPerMessageDeflateCompressor compressor;
        ix::WebSocketPerMessageDeflateDecompressor decoder;
        CHECK(compressor.init(15, true));
        CHECK(decoder.init(15, true));
        std::string input(8 * 1024 * 1024, 'a'), compressed, output;
        CHECK(compressor.compress(input, compressed));
        CHECK(decoder.decompress(compressed, output));
        CHECK(output == input);
        input.push_back('a');
        CHECK(compressor.compress(input, compressed));
        CHECK(!decoder.decompress(compressed, output));
        CHECK(output.empty());
    });
}
