// Description: DPLL subsystem.
//
// Code generated by yamlnetlink-go. DO NOT EDIT.
package dpll

import (
	"errors"

	"github.com/mdlayher/genetlink"
	"github.com/mdlayher/netlink"
	"golang.org/x/sys/unix"
)

// A Conn is a connection to netlink family "dpll".
type Conn struct {
	c *genetlink.Conn
	f genetlink.Family
}

// Dial opens a Conn for netlink family "dpll". Any options are passed directly
// to the underlying netlink package.
func Dial(cfg *netlink.Config) (*Conn, error) {
	c, err := genetlink.Dial(cfg)
	if err != nil {
		return nil, err
	}

	f, err := c.GetFamily("dpll")
	if err != nil {
		return nil, err
	}

	return &Conn{c: c, f: f}, nil
}

// Close closes the Conn's underlying netlink connection.
func (c *Conn) Close() error { return c.c.Close() }

// DoDeviceIdGet wraps the "device-id-get" operation:
// Get id of dpll device that matches given attributes

func (c *Conn) DoDeviceIdGet(req DoDeviceIdGetRequest) (*DoDeviceIdGetReply, error) {
	ae := netlink.NewAttributeEncoder()
	// TODO: field "req.ModuleName", type "string"
	if req.ClockId != 0 {
		ae.Uint64(unix.DPLL_A_DPLL_CLOCK_ID, req.ClockId)
	}
	if req.Type != 0 {
		ae.Uint8(unix.DPLL_A_DPLL_TYPE, req.Type)
	}

	b, err := ae.Encode()
	if err != nil {
		return nil, err
	}

	msg := genetlink.Message{
		Header: genetlink.Header{
			Command: unix.DEVICE_ID_GET,
			Version: c.f.Version,
		},
		Data: b,
	}

	msgs, err := c.c.Execute(msg, c.f.ID, netlink.Request)
	if err != nil {
		return nil, err
	}

	replies := make([]*DoDeviceIdGetReply, 0, len(msgs))
	for _, m := range msgs {
		ad, err := netlink.NewAttributeDecoder(m.Data)
		if err != nil {
			return nil, err
		}

		var reply DoDeviceIdGetReply
		for ad.Next() {
			switch ad.Type() {
			case unix.DPLL_A_DPLL_ID:
				reply.Id = ad.Uint32()
			}
		}

		if err := ad.Err(); err != nil {
			return nil, err
		}

		replies = append(replies, &reply)
	}

	if len(replies) != 1 {
		return nil, errors.New("dpll: expected exactly one DoDeviceIdGetReply")
	}

	return replies[0], nil
}

// DoDeviceIdGetRequest is used with the DoDeviceIdGet method.
type DoDeviceIdGetRequest struct {
	// TODO: field "ModuleName", type "string"
	ClockId uint64
	Type    uint8
}

// DoDeviceIdGetReply is used with the DoDeviceIdGet method.
type DoDeviceIdGetReply struct {
	Id uint32
}

// DoDeviceGet wraps the "device-get" operation:
// Get list of DPLL devices (dump) or attributes of a single dpll device

func (c *Conn) DoDeviceGet(req DoDeviceGetRequest) (*DoDeviceGetReply, error) {
	ae := netlink.NewAttributeEncoder()
	if req.Id != 0 {
		ae.Uint32(unix.DPLL_A_DPLL_ID, req.Id)
	}
	// TODO: field "req.ModuleName", type "string"

	b, err := ae.Encode()
	if err != nil {
		return nil, err
	}

	msg := genetlink.Message{
		Header: genetlink.Header{
			Command: unix.DEVICE_GET,
			Version: c.f.Version,
		},
		Data: b,
	}

	msgs, err := c.c.Execute(msg, c.f.ID, netlink.Request)
	if err != nil {
		return nil, err
	}

	replies := make([]*DoDeviceGetReply, 0, len(msgs))
	for _, m := range msgs {
		ad, err := netlink.NewAttributeDecoder(m.Data)
		if err != nil {
			return nil, err
		}

		var reply DoDeviceGetReply
		for ad.Next() {
			switch ad.Type() {
			case unix.DPLL_A_DPLL_ID:
				reply.Id = ad.Uint32()
			case unix.DPLL_A_DPLL_MODULE_NAME:
				// TODO: field "reply.ModuleName", type "string"
			case unix.DPLL_A_DPLL_MODE:
				reply.Mode = ad.Uint8()
			case unix.DPLL_A_DPLL_MODE_SUPPORTED:
				reply.ModeSupported = ad.Uint8()
			case unix.DPLL_A_DPLL_LOCK_STATUS:
				reply.LockStatus = ad.Uint8()
			case unix.DPLL_A_DPLL_TEMP:
				// TODO: field "reply.Temp", type "s32"
			case unix.DPLL_A_DPLL_CLOCK_ID:
				reply.ClockId = ad.Uint64()
			case unix.DPLL_A_DPLL_TYPE:
				reply.Type = ad.Uint8()
			}
		}

		if err := ad.Err(); err != nil {
			return nil, err
		}

		replies = append(replies, &reply)
	}

	if len(replies) != 1 {
		return nil, errors.New("dpll: expected exactly one DoDeviceGetReply")
	}

	return replies[0], nil
}

// DumpDeviceGet wraps the "device-get" operation:
// Get list of DPLL devices (dump) or attributes of a single dpll device

func (c *Conn) DumpDeviceGet() ([]*DumpDeviceGetReply, error) {
	// No attribute arguments.
	var b []byte

	msg := genetlink.Message{
		Header: genetlink.Header{
			Command: unix.DEVICE_GET,
			Version: c.f.Version,
		},
		Data: b,
	}

	msgs, err := c.c.Execute(msg, c.f.ID, netlink.Request|netlink.Dump)
	if err != nil {
		return nil, err
	}

	replies := make([]*DumpDeviceGetReply, 0, len(msgs))
	for _, m := range msgs {
		ad, err := netlink.NewAttributeDecoder(m.Data)
		if err != nil {
			return nil, err
		}

		var reply DumpDeviceGetReply
		for ad.Next() {
			switch ad.Type() {
			case unix.DPLL_A_DPLL_ID:
				reply.Id = ad.Uint32()
			case unix.DPLL_A_DPLL_MODULE_NAME:
				// TODO: field "reply.ModuleName", type "string"
			case unix.DPLL_A_DPLL_MODE:
				reply.Mode = ad.Uint8()
			case unix.DPLL_A_DPLL_MODE_SUPPORTED:
				reply.ModeSupported = ad.Uint8()
			case unix.DPLL_A_DPLL_LOCK_STATUS:
				reply.LockStatus = ad.Uint8()
			case unix.DPLL_A_DPLL_TEMP:
				// TODO: field "reply.Temp", type "s32"
			case unix.DPLL_A_DPLL_CLOCK_ID:
				reply.ClockId = ad.Uint64()
			case unix.DPLL_A_DPLL_TYPE:
				reply.Type = ad.Uint8()
			}
		}

		if err := ad.Err(); err != nil {
			return nil, err
		}

		replies = append(replies, &reply)
	}

	return replies, nil
}

// DoDeviceGetRequest is used with the DoDeviceGet method.
type DoDeviceGetRequest struct {
	Id uint32
	// TODO: field "ModuleName", type "string"
}

// DoDeviceGetReply is used with the DoDeviceGet method.
type DoDeviceGetReply struct {
	Id uint32
	// TODO: field "ModuleName", type "string"
	Mode          uint8
	ModeSupported uint8
	LockStatus    uint8
	// TODO: field "Temp", type "s32"
	ClockId uint64
	Type    uint8
}

// DumpDeviceGetReply is used with the DumpDeviceGet method.
type DumpDeviceGetReply struct {
	Id uint32
	// TODO: field "ModuleName", type "string"
	Mode          uint8
	ModeSupported uint8
	LockStatus    uint8
	// TODO: field "Temp", type "s32"
	ClockId uint64
	Type    uint8
}

// DoDeviceSet wraps the "device-set" operation:
// Set attributes for a DPLL device
func (c *Conn) DoDeviceSet(req DoDeviceSetRequest) error {
	ae := netlink.NewAttributeEncoder()
	if req.Id != 0 {
		ae.Uint32(unix.DPLL_A_DPLL_ID, req.Id)
	}
	if req.Mode != 0 {
		ae.Uint8(unix.DPLL_A_DPLL_MODE, req.Mode)
	}

	b, err := ae.Encode()
	if err != nil {
		return err
	}

	msg := genetlink.Message{
		Header: genetlink.Header{
			Command: unix.DEVICE_SET,
			Version: c.f.Version,
		},
		Data: b,
	}

	// No replies.
	_, err = c.c.Execute(msg, c.f.ID, netlink.Request)
	return err
}

// DoDeviceSetRequest is used with the DoDeviceSet method.
type DoDeviceSetRequest struct {
	Id   uint32
	Mode uint8
}

// DoPinIdGet wraps the "pin-id-get" operation:
// Get id of a pin that matches given attributes

func (c *Conn) DoPinIdGet(req DoPinIdGetRequest) (*DoPinIdGetReply, error) {
	ae := netlink.NewAttributeEncoder()
	// TODO: field "req.ModuleName", type "string"
	if req.ClockId != 0 {
		ae.Uint64(unix.DPLL_A_DPLL_CLOCK_ID, req.ClockId)
	}
	// TODO: field "req.PinBoardLabel", type "string"
	// TODO: field "req.PinPanelLabel", type "string"
	// TODO: field "req.PinPackageLabel", type "string"
	if req.PinType != 0 {
		ae.Uint8(unix.DPLL_A_DPLL_PIN_TYPE, req.PinType)
	}

	b, err := ae.Encode()
	if err != nil {
		return nil, err
	}

	msg := genetlink.Message{
		Header: genetlink.Header{
			Command: unix.PIN_ID_GET,
			Version: c.f.Version,
		},
		Data: b,
	}

	msgs, err := c.c.Execute(msg, c.f.ID, netlink.Request)
	if err != nil {
		return nil, err
	}

	replies := make([]*DoPinIdGetReply, 0, len(msgs))
	for _, m := range msgs {
		ad, err := netlink.NewAttributeDecoder(m.Data)
		if err != nil {
			return nil, err
		}

		var reply DoPinIdGetReply
		for ad.Next() {
			switch ad.Type() {
			case unix.DPLL_A_DPLL_ID:
				reply.Id = ad.Uint32()
			}
		}

		if err := ad.Err(); err != nil {
			return nil, err
		}

		replies = append(replies, &reply)
	}

	if len(replies) != 1 {
		return nil, errors.New("dpll: expected exactly one DoPinIdGetReply")
	}

	return replies[0], nil
}

// DoPinIdGetRequest is used with the DoPinIdGet method.
type DoPinIdGetRequest struct {
	// TODO: field "ModuleName", type "string"
	ClockId uint64
	// TODO: field "PinBoardLabel", type "string"
	// TODO: field "PinPanelLabel", type "string"
	// TODO: field "PinPackageLabel", type "string"
	PinType uint8
}

// DoPinIdGetReply is used with the DoPinIdGet method.
type DoPinIdGetReply struct {
	Id uint32
}

// DoPinGet wraps the "pin-get" operation:
// Get list of pins and its attributes.
// - dump request without any attributes given - list all the pins in the
//   system
// - dump request with target dpll - list all the pins registered with
//   a given dpll device
// - do request with target dpll and target pin - single pin attributes

func (c *Conn) DoPinGet(req DoPinGetRequest) (*DoPinGetReply, error) {
	ae := netlink.NewAttributeEncoder()
	if req.Id != 0 {
		ae.Uint32(unix.DPLL_A_DPLL_ID, req.Id)
	}
	if req.PinId != 0 {
		ae.Uint32(unix.DPLL_A_DPLL_PIN_ID, req.PinId)
	}

	b, err := ae.Encode()
	if err != nil {
		return nil, err
	}

	msg := genetlink.Message{
		Header: genetlink.Header{
			Command: unix.PIN_GET,
			Version: c.f.Version,
		},
		Data: b,
	}

	msgs, err := c.c.Execute(msg, c.f.ID, netlink.Request)
	if err != nil {
		return nil, err
	}

	replies := make([]*DoPinGetReply, 0, len(msgs))
	for _, m := range msgs {
		ad, err := netlink.NewAttributeDecoder(m.Data)
		if err != nil {
			return nil, err
		}

		var reply DoPinGetReply
		for ad.Next() {
			switch ad.Type() {
			case unix.DPLL_A_DPLL_PIN_ID:
				reply.PinId = ad.Uint32()
			case unix.DPLL_A_DPLL_PIN_BOARD_LABEL:
				// TODO: field "reply.PinBoardLabel", type "string"
			case unix.DPLL_A_DPLL_PIN_PANEL_LABEL:
				// TODO: field "reply.PinPanelLabel", type "string"
			case unix.DPLL_A_DPLL_PIN_PACKAGE_LABEL:
				// TODO: field "reply.PinPackageLabel", type "string"
			case unix.DPLL_A_DPLL_PIN_TYPE:
				reply.PinType = ad.Uint8()
			case unix.DPLL_A_DPLL_PIN_FREQUENCY:
				reply.PinFrequency = ad.Uint64()
			case unix.DPLL_A_DPLL_PIN_FREQUENCY_SUPPORTED:
				ad.Nested(func(ad *netlink.AttributeDecoder) error {
					for ad.Next() {
						switch ad.Type() {
						case unix.DPLL_A_PIN_FREQUENCY_RANGE_PIN_FREQUENCY_MIN:
							reply.PinFrequencySupported.PinFrequencyMin = ad.Uint64()
						case unix.DPLL_A_PIN_FREQUENCY_RANGE_PIN_FREQUENCY_MAX:
							reply.PinFrequencySupported.PinFrequencyMax = ad.Uint64()
						}
					}

					return nil
				})
			case unix.DPLL_A_DPLL_PIN_PARENT:
				ad.Nested(func(ad *netlink.AttributeDecoder) error {
					for ad.Next() {
						switch ad.Type() {
						case unix.DPLL_A_PIN_PARENT_ID:
							reply.PinParent.Id = ad.Uint32()
						case unix.DPLL_A_PIN_PARENT_PIN_DIRECTION:
							reply.PinParent.PinDirection = ad.Uint8()
						case unix.DPLL_A_PIN_PARENT_PIN_PRIO:
							reply.PinParent.PinPrio = ad.Uint32()
						case unix.DPLL_A_PIN_PARENT_PIN_STATE:
							reply.PinParent.PinState = ad.Uint8()
						case unix.DPLL_A_PIN_PARENT_PIN_ID:
							reply.PinParent.PinId = ad.Uint32()
						}
					}

					return nil
				})
			case unix.DPLL_A_DPLL_PIN_DPLL_CAPS:
				reply.PinDpllCaps = ad.Uint32()
			}
		}

		if err := ad.Err(); err != nil {
			return nil, err
		}

		replies = append(replies, &reply)
	}

	if len(replies) != 1 {
		return nil, errors.New("dpll: expected exactly one DoPinGetReply")
	}

	return replies[0], nil
}

// DumpPinGet wraps the "pin-get" operation:
// Get list of pins and its attributes.
// - dump request without any attributes given - list all the pins in the
//   system
// - dump request with target dpll - list all the pins registered with
//   a given dpll device
// - do request with target dpll and target pin - single pin attributes

func (c *Conn) DumpPinGet(req DumpPinGetRequest) ([]*DumpPinGetReply, error) {
	ae := netlink.NewAttributeEncoder()
	if req.Id != 0 {
		ae.Uint32(unix.DPLL_A_DPLL_ID, req.Id)
	}

	b, err := ae.Encode()
	if err != nil {
		return nil, err
	}

	msg := genetlink.Message{
		Header: genetlink.Header{
			Command: unix.PIN_GET,
			Version: c.f.Version,
		},
		Data: b,
	}

	msgs, err := c.c.Execute(msg, c.f.ID, netlink.Request|netlink.Dump)
	if err != nil {
		return nil, err
	}

	replies := make([]*DumpPinGetReply, 0, len(msgs))
	for _, m := range msgs {
		ad, err := netlink.NewAttributeDecoder(m.Data)
		if err != nil {
			return nil, err
		}

		var reply DumpPinGetReply
		for ad.Next() {
			switch ad.Type() {
			case unix.DPLL_A_DPLL_PIN_ID:
				reply.PinId = ad.Uint32()
			case unix.DPLL_A_DPLL_PIN_BOARD_LABEL:
				// TODO: field "reply.PinBoardLabel", type "string"
			case unix.DPLL_A_DPLL_PIN_PANEL_LABEL:
				// TODO: field "reply.PinPanelLabel", type "string"
			case unix.DPLL_A_DPLL_PIN_PACKAGE_LABEL:
				// TODO: field "reply.PinPackageLabel", type "string"
			case unix.DPLL_A_DPLL_PIN_TYPE:
				reply.PinType = ad.Uint8()
			case unix.DPLL_A_DPLL_PIN_FREQUENCY:
				reply.PinFrequency = ad.Uint64()
			case unix.DPLL_A_DPLL_PIN_FREQUENCY_SUPPORTED:
				ad.Nested(func(ad *netlink.AttributeDecoder) error {
					for ad.Next() {
						switch ad.Type() {
						case unix.DPLL_A_PIN_FREQUENCY_RANGE_PIN_FREQUENCY_MIN:
							reply.PinFrequencySupported.PinFrequencyMin = ad.Uint64()
						case unix.DPLL_A_PIN_FREQUENCY_RANGE_PIN_FREQUENCY_MAX:
							reply.PinFrequencySupported.PinFrequencyMax = ad.Uint64()
						}
					}

					return nil
				})
			case unix.DPLL_A_DPLL_PIN_PARENT:
				ad.Nested(func(ad *netlink.AttributeDecoder) error {
					for ad.Next() {
						switch ad.Type() {
						case unix.DPLL_A_PIN_PARENT_ID:
							reply.PinParent.Id = ad.Uint32()
						case unix.DPLL_A_PIN_PARENT_PIN_DIRECTION:
							reply.PinParent.PinDirection = ad.Uint8()
						case unix.DPLL_A_PIN_PARENT_PIN_PRIO:
							reply.PinParent.PinPrio = ad.Uint32()
						case unix.DPLL_A_PIN_PARENT_PIN_STATE:
							reply.PinParent.PinState = ad.Uint8()
						case unix.DPLL_A_PIN_PARENT_PIN_ID:
							reply.PinParent.PinId = ad.Uint32()
						}
					}

					return nil
				})
			case unix.DPLL_A_DPLL_PIN_DPLL_CAPS:
				reply.PinDpllCaps = ad.Uint32()
			}
		}

		if err := ad.Err(); err != nil {
			return nil, err
		}

		replies = append(replies, &reply)
	}

	return replies, nil
}

// DoPinGetRequest is used with the DoPinGet method.
type DoPinGetRequest struct {
	Id    uint32
	PinId uint32
}

// DoPinGetReply is used with the DoPinGet method.
type DoPinGetReply struct {
	PinId uint32
	// TODO: field "PinBoardLabel", type "string"
	// TODO: field "PinPanelLabel", type "string"
	// TODO: field "PinPackageLabel", type "string"
	PinType               uint8
	PinFrequency          uint64
	PinFrequencySupported PinFrequencyRange
	PinParent             PinParent
	PinDpllCaps           uint32
}

// PinFrequencyRange contains nested netlink attributes.
type PinFrequencyRange struct {
	PinFrequencyMin uint64
	PinFrequencyMax uint64
}

// PinParent contains nested netlink attributes.
type PinParent struct {
	Id           uint32
	PinDirection uint8
	PinPrio      uint32
	PinState     uint8
	PinId        uint32
}

// DumpPinGetRequest is used with the DumpPinGet method.
type DumpPinGetRequest struct {
	Id uint32
}

// DumpPinGetReply is used with the DumpPinGet method.
type DumpPinGetReply struct {
	PinId uint32
	// TODO: field "PinBoardLabel", type "string"
	// TODO: field "PinPanelLabel", type "string"
	// TODO: field "PinPackageLabel", type "string"
	PinType               uint8
	PinFrequency          uint64
	PinFrequencySupported PinFrequencyRange
	PinParent             PinParent
	PinDpllCaps           uint32
}

// DoPinSet wraps the "pin-set" operation:
// Set attributes of a target pin
func (c *Conn) DoPinSet(req DoPinSetRequest) error {
	ae := netlink.NewAttributeEncoder()
	if req.Id != 0 {
		ae.Uint32(unix.DPLL_A_DPLL_ID, req.Id)
	}
	if req.PinId != 0 {
		ae.Uint32(unix.DPLL_A_DPLL_PIN_ID, req.PinId)
	}
	if req.PinFrequency != 0 {
		ae.Uint64(unix.DPLL_A_DPLL_PIN_FREQUENCY, req.PinFrequency)
	}
	if req.PinDirection != 0 {
		ae.Uint8(unix.DPLL_A_DPLL_PIN_DIRECTION, req.PinDirection)
	}
	if req.PinPrio != 0 {
		ae.Uint32(unix.DPLL_A_DPLL_PIN_PRIO, req.PinPrio)
	}
	if req.PinState != 0 {
		ae.Uint8(unix.DPLL_A_DPLL_PIN_STATE, req.PinState)
	}
	ae.Nested(unix.DPLL_A_DPLL_PIN_PARENT, func(ae *netlink.AttributeEncoder) error {
		if req.PinParent.Id != 0 {
			ae.Uint32(unix.DPLL_A_PIN_PARENT_ID, req.PinParent.Id)
		}
		if req.PinParent.PinDirection != 0 {
			ae.Uint8(unix.DPLL_A_PIN_PARENT_PIN_DIRECTION, req.PinParent.PinDirection)
		}
		if req.PinParent.PinPrio != 0 {
			ae.Uint32(unix.DPLL_A_PIN_PARENT_PIN_PRIO, req.PinParent.PinPrio)
		}
		if req.PinParent.PinState != 0 {
			ae.Uint8(unix.DPLL_A_PIN_PARENT_PIN_STATE, req.PinParent.PinState)
		}
		if req.PinParent.PinId != 0 {
			ae.Uint32(unix.DPLL_A_PIN_PARENT_PIN_ID, req.PinParent.PinId)
		}

		return nil
	})

	b, err := ae.Encode()
	if err != nil {
		return err
	}

	msg := genetlink.Message{
		Header: genetlink.Header{
			Command: unix.PIN_SET,
			Version: c.f.Version,
		},
		Data: b,
	}

	// No replies.
	_, err = c.c.Execute(msg, c.f.ID, netlink.Request)
	return err
}

// DoPinSetRequest is used with the DoPinSet method.
type DoPinSetRequest struct {
	Id           uint32
	PinId        uint32
	PinFrequency uint64
	PinDirection uint8
	PinPrio      uint32
	PinState     uint8
	PinParent    PinParent
}
