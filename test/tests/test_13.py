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

    def test_THC_pause(self):
        # shift positions according to autohome
        decoder.apply_autohome(self.timeline, events[20] + 2)
        self.timeline[3] += 10000

        # end of homing and ohmic probing
        slice = decoder.from_to(self.timeline, self.events[20] + 2, self.events[21])
        assert decoder.move_diff(slice, 1) == 1000
        assert decoder.move_diff(slice, 2) == 1000
        assert decoder.move_cumul_down(slice, 3) > 1000
        assert decoder.move_cumul_up(slice, 3) == 0

        # z retract 3mm on probing
        slice = decoder.from_to(self.timeline, self.events[21] + 2, self.events[22])
        assert decoder.move_cumul_up(slice, 3) == 300
        assert decoder.move_cumul_down(slice, 3) == 0

        # pause 500ms
        slice = decoder.from_to(self.timeline, self.events[22], self.events[22] + 500)
        assert decoder.move_cumul(slice, 3) == 0

        # z move enough with THC until M5
        slice = decoder.from_to(self.timeline, self.events[23] - 1000, self.events[23])
        assert decoder.move_cumul(slice, 3) > 2000

        # wait for resume
        slice = decoder.from_to(self.timeline, self.events[27], self.events[28])
        assert decoder.move_cumul(slice, 1) == 0
        assert decoder.move_cumul(slice, 2) == 0
        assert decoder.move_cumul(slice, 3) == 0

        # z goes back to top
        slice = decoder.from_to(self.timeline, self.events[28], self.events[29])
        assert decoder.max_pos(slice, 3) == 10000

        # axis in place for next cut
        before_probing = decoder.when_is_position_reached(slice, 1000, 2000, 10000)
        assert before_probing != -1

        # ohmic probing
        slice = decoder.from_to(self.timeline, before_probing, self.events[29])
        assert decoder.move_cumul_down(slice, 3) > 1000
        assert decoder.move_cumul_up(slice, 3) == 0

        # z retract 3mm on probing
        slice = decoder.from_to(self.timeline, self.events[29] + 2, self.events[30])
        assert decoder.move_cumul_up(slice, 3) == 300
        assert decoder.move_cumul_down(slice, 3) == 0

        # z move enough with THC until M5
        slice = decoder.from_to(self.timeline, self.events[31] - 1000, self.events[31])
        assert decoder.move_cumul(slice, 3) > 2000

export_basename = 'tmp/' + os.path.splitext(os.path.basename(__file__))[0]
p = player.Player(export_basename)

p.click()
p.move_down()
p.move_down()
p.move_down()
p.click()
p.move_down()
p.move_down()
p.move_down()
p.move_down()
p.move_down()
p.move_down()
p.move_down()
p.move_down()
p.move_down()
p.click()

p.endstop_z()
p.wait_ms(300)
p.endstop_z()
p.wait_ms(100)
p.endstop_x()
p.wait_ms(300)
p.endstop_x()
p.wait_ms(100)
p.endstop_y()
p.wait_ms(300)
p.endstop_y()
p.wait_ms(1000)
p.ohmic_probe()
p.wait_ms(100)
p.transfer_on()
p.wait_ms(1000)

# pause
p.click()
p.move_down()
p.move_down()
p.click()

p.wait_ms(1100)
p.transfer_off()
p.wait_ms(1000)

# resume
p.click()

p.wait_ms(1600)
p.ohmic_probe()
p.wait_ms(100)
p.transfer_on()
p.wait_ms(1500)
p.transfer_off()

events = p.run()

timeline = decoder.decode(export_basename + '.bin')

p.close()