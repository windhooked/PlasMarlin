#!/usr/bin/env python3
import os
import utils.player as player
import utils.decoder as decoder

class Test:
    def setup(self):
        global events
        global timeline
        self.events = events
        self.timeline = timeline

    def test_M3_no_M5(self):
        # motors reach firing position
        self.plasma_start = decoder.when_is_position_reached(timeline, 500, 500, 0)
        assert self.plasma_start != -1

        # motors reach cutoff position
        slice = decoder.from_to(self.timeline, self.plasma_start, decoder.end(timeline))
        self.plasma_stop = decoder.when_is_position_reached(slice, 0, 0, 0)
        assert self.plasma_stop != -1

        # no plasma before cut
        slice = decoder.from_to(self.timeline, 0, self.plasma_start)
        assert decoder.plasma_is_always(slice, 'off')

        # plasma fired all along
        slice = decoder.from_to(self.timeline, self.plasma_start + 5, self.plasma_stop)
        assert decoder.plasma_is_always(slice, 'on')

        # no plasma after cut off
        slice = decoder.from_to(self.timeline, self.plasma_stop + 2, decoder.end(timeline))
        assert decoder.plasma_is_always(slice, 'off')

export_basename = 'tmp/' + os.path.splitext(os.path.basename(__file__))[0]
p = player.Player(export_basename)

p.click()
p.move_down()
p.move_down()
p.move_down()
p.click()
p.move_down()
p.move_down()
p.click()
p.transfer_on()
p.wait_ms(600)
p.transfer_off()

events = p.run()

timeline = decoder.decode(export_basename + '.bin')

p.close()