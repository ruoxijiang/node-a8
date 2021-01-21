const expect = require('chai').expect;
const a8 = require('../lib/index');
const fs = require('fs');
const rimraf = require('rimraf');
describe('A8', function () {
  before(function () {
    return new Promise((resolve) => {
      const onRemovedFiles = () => {
        console.log('creating tmp dir');
        fs.mkdir('./test/data', resolve);
      };
      console.log('clearing tmp dir');
      rimraf('./test/data', { disableGlob: true }, onRemovedFiles);
    });
  });
  beforeEach(function () {
    a8.init({ workingDir: './test/data/' });
    console.log('a8 initialized');
  });
  // it('LinkedIn Profile', function (done) {
  //   this.timeout(15000);
  //   const profile = {
  //     name: 'Weicheng Qian',
  //     email: 'weicheng@hotmail.com',
  //     organization: 'Edison',
  //     organizationSource: 'public',
  //     title: '',
  //     owner: 'unit test',
  //   };
  //   a8.fetchLinkedInProfile({
  //     profile,
  //     onOk: (ret) => {
  //       console.log(`linkedin profile result ${JSON.stringify(ret)}`);
  //       expect(ret.updateTime).greaterThan(0);
  //       done();
  //     },
  //     onError: (ret) => {
  //       console.log(ret);
  //     },
  //   });
  // });
  it('CheckHeaders: should return 0', function (done) {
    this.timeout(2000);
    const additionalHeaders = {
      'ARC-Authentication-Results':
        'i=3; mx.google.com; dkim=pass\r\n header.i=@edison-tech.20150623.gappssmtp.com header.s=20150623\r\n header.b=gdijKgPv; arc=pass (i=2 dkim=pass\r\n dkdomain=edison-tech.20150623.gappssmtp.com); spf=neutral (google.com:\r\n 209.85.220.69 is neither permitted nor denied by best guess record for domain\r\n of client+bncbcl2loepzalbbye5ql7qkgqe3m34ynq@edison.tech)\r\n smtp.mailfrom=client+bncBCL2LOEPZALBBYE5QL7QKGQE3M34YNQ@edison.tech',
      'ARC-Message-Signature':
        'i=3; a=rsa-sha256; c=relaxed/relaxed; d=google.com;\r\n s=arc-20160816; h=list-unsubscribe:list-archive:list-help:list-post:list-id\r\n :mailing-list:precedence:cc:to:subject:message-id:date:from\r\n :mime-version:dkim-signature;\r\n bh=rXAZeCVxn6wh+P35x8yTj/9N1bBeS/hYq9tKvFtQQ/w=;\r\n b=mzUhehlnLEzmADUr2rbgsPkt8DKpr1egrM7rMoZfYDqdZsiMDouso4u+ZN1LbzLpuy\r\n ig7h/+Y4VgF7IJAAw+ZfWQI+tSv0o3cmEoTiMUzhpJ4goZ8yopYayaSX+RauqddsRZ3a\r\n MRyvqWMBHsXUga74P1fVq3B4YmXF6/YUzWNPQbhN94dZa2vRe2rKs99dUmgt4g4k9m6Q\r\n eRi0T7bgIiBLYrPk7AMz0l47N0+D7oDYHPMnkDyJk5dhXULMdthBXdem13QfvtFv+J6Y\r\n BPugRx5L7qJf65pyc2aBpAxpiEc7wD/1PIByMUKak1tTCpVwRvutQvWBCLsSDTcJm+BS 6aYA==',
      'ARC-Seal':
        'i=3; a=rsa-sha256; t=1608552161; cv=pass; d=google.com;\r\n s=arc-20160816;\r\n b=r8cjfIuQvk4Y/lRFu4Cu3mH88rB1cqVhm9anqajxiSuyANwvQ2shmmyV0YzjwkGTpT\r\n xxlng9OUi7CyJIiqUCsw+Mq8t4GUifUurZZH0xjgDV9q5SQX4npZ0+cPdJabFi8KFoB7\r\n AbatDHuCbffyWBogsildqrXveV4weQOY64ZilFMAHOfUJrrzXifhtVUthTpa4Y/76EbF\r\n fyVsEzNBmZdvLO07mL4bXyyceBsNZAuHw7zm4Gffrh/O2HR3q1KGHDxXMxVC1VpRQDDW\r\n k/VS3Ce2x1gtYDB3q7uuOY8FvtQgTxUYx51JlVKAE8na4XRcZu2DJbtkRvLgWXuBnX+0 Ougg==',
      'Authentication-Results':
        'mx.google.com; dkim=pass\r\n header.i=@edison-tech.20150623.gappssmtp.com header.s=20150623\r\n header.b=gdijKgPv; arc=pass (i=2 dkim=pass\r\n dkdomain=edison-tech.20150623.gappssmtp.com); spf=neutral (google.com:\r\n 209.85.220.69 is neither permitted nor denied by best guess record for domain\r\n of client+bncbcl2loepzalbbye5ql7qkgqe3m34ynq@edison.tech)\r\n smtp.mailfrom=client+bncBCL2LOEPZALBBYE5QL7QKGQE3M34YNQ@edison.tech',
      'DKIM-Signature':
        'v=1; a=rsa-sha256; c=relaxed/relaxed;\r\n d=edison-tech.20150623.gappssmtp.com; s=20150623;\r\n h=mime-version:from:date:message-id:subject:to:cc:x-original-sender\r\n :x-original-authentication-results:precedence:mailing-list:list-id\r\n :list-post:list-help:list-archive:list-unsubscribe;\r\n bh=rXAZeCVxn6wh+P35x8yTj/9N1bBeS/hYq9tKvFtQQ/w=;\r\n b=gdijKgPvDUxFjwQ2dWFDzIaROD/nNkOULWEcNjA4sCEe212XYT133nVPDwxERVCYy/\r\n wSONDZrMbLXPgoC4lsiO8wLdDfteaqbe2xYzQoOmFa4d29g+o9XOO9LE7ywm3cYEs4i3\r\n Ar+ynGHQwytBzj6LIx2AvD4mBUfS7Ipc1U4nLSPZSxlnrcLPfxXNDUGKwuiWOdgAeyPL\r\n bri6FdmOQNsyuG0uYTVr3XhD/rG20kW2JG3PcS+jVBy1dnbyogq/6lZt30NJSO86W21l\r\n 1yIvFPppa4uw72XeFl10RLrcM2ypev3e1IPfa/UvMcH4+bo7bWP5AuLlVRWxOhEahL8M UHSg==',
      ListId: '<client.edison.tech>',
      ListUnsub:
        '<mailto:googlegroups-manage+1044890630547+unsubscribe@googlegroups.com>,\r\n <https://groups.google.com/a/edison.tech/group/client/subscribe>',
      Received: [
        'by 2002:a0c:fa4d:0:0:0:0:0 with SMTP id k13csp4532278qvo; Mon, 21\r\n Dec 2020 04:02:41 -0800 (PST)',
        'from mail-sor-f69.google.com (mail-sor-f69.google.com.\r\n [209.85.220.69]) by mx.google.com with SMTPS id\r\n f13sor9183974ioq.81.2020.12.21.04.02.41 for <ruoxi@edison.tech> (Google\r\n Transport Security); Mon, 21 Dec 2020 04:02:41 -0800 (PST)',
        'by 2002:a02:cab9:: with SMTP id e25ls4575396jap.9.gmail; Mon, 21 Dec\r\n 2020 04:02:40 -0800 (PST)',
        'from mail-sor-f41.google.com (mail-sor-f41.google.com.\r\n [209.85.220.41]) by mx.google.com with SMTPS id\r\n b3sor9033772ioz.19.2020.12.21.04.02.40 for <client@edison.tech> (Google\r\n Transport Security); Mon, 21 Dec 2020 04:02:40 -0800 (PST)',
      ],
      'Return-Path': '<client+bncBCL2LOEPZALBBYE5QL7QKGQE3M34YNQ@edison.tech>',
    };
    const headers = [
      { type: 0, header: 'From', value: 'ruoxi@edisoon.tech' },
      {
        type: 1,
        header: 'To',
        values: ['edison_test@outlook.com', 'easilydo_zhou@163.com'],
      },
    ];
    Object.keys(additionalHeaders).forEach((key) => {
      if (typeof additionalHeaders[key] === 'string') {
        headers.push({ type: 0, header: key, value: additionalHeaders[key] });
      } else {
        headers.push({ type: 1, header: key, values: additionalHeaders[key] });
      }
    });
    const extraInfo = { isStranger: false, isColleague: false, isWellKnownProvider: true };
    try {
      a8.checkHeader({
        headers,
        extraCheckInfo: extraInfo,
        onOk: (ret) => {
          console.log(`Results returned ${ret}`);
          expect(ret).equal(0);
          done();
        },
      });
    } catch (e) {
      console.log(e);
    }
  });
  // it('checkEmail: should return 1', function (done) {
  //   this.timeout(5000);
  //   const additionalHeaders = {
  //     'ARC-Authentication-Results':
  //       'i=3; mx.google.com; dkim=pass\r\n header.i=@edison-tech.20150623.gappssmtp.com header.s=20150623\r\n header.b=gdijKgPv; arc=pass (i=2 dkim=pass\r\n dkdomain=edison-tech.20150623.gappssmtp.com); spf=neutral (google.com:\r\n 209.85.220.69 is neither permitted nor denied by best guess record for domain\r\n of client+bncbcl2loepzalbbye5ql7qkgqe3m34ynq@edison.tech)\r\n smtp.mailfrom=client+bncBCL2LOEPZALBBYE5QL7QKGQE3M34YNQ@edison.tech',
  //     'ARC-Message-Signature':
  //       'i=3; a=rsa-sha256; c=relaxed/relaxed; d=google.com;\r\n s=arc-20160816; h=list-unsubscribe:list-archive:list-help:list-post:list-id\r\n :mailing-list:precedence:cc:to:subject:message-id:date:from\r\n :mime-version:dkim-signature;\r\n bh=rXAZeCVxn6wh+P35x8yTj/9N1bBeS/hYq9tKvFtQQ/w=;\r\n b=mzUhehlnLEzmADUr2rbgsPkt8DKpr1egrM7rMoZfYDqdZsiMDouso4u+ZN1LbzLpuy\r\n ig7h/+Y4VgF7IJAAw+ZfWQI+tSv0o3cmEoTiMUzhpJ4goZ8yopYayaSX+RauqddsRZ3a\r\n MRyvqWMBHsXUga74P1fVq3B4YmXF6/YUzWNPQbhN94dZa2vRe2rKs99dUmgt4g4k9m6Q\r\n eRi0T7bgIiBLYrPk7AMz0l47N0+D7oDYHPMnkDyJk5dhXULMdthBXdem13QfvtFv+J6Y\r\n BPugRx5L7qJf65pyc2aBpAxpiEc7wD/1PIByMUKak1tTCpVwRvutQvWBCLsSDTcJm+BS 6aYA==',
  //     'ARC-Seal':
  //       'i=3; a=rsa-sha256; t=1608552161; cv=pass; d=google.com;\r\n s=arc-20160816;\r\n b=r8cjfIuQvk4Y/lRFu4Cu3mH88rB1cqVhm9anqajxiSuyANwvQ2shmmyV0YzjwkGTpT\r\n xxlng9OUi7CyJIiqUCsw+Mq8t4GUifUurZZH0xjgDV9q5SQX4npZ0+cPdJabFi8KFoB7\r\n AbatDHuCbffyWBogsildqrXveV4weQOY64ZilFMAHOfUJrrzXifhtVUthTpa4Y/76EbF\r\n fyVsEzNBmZdvLO07mL4bXyyceBsNZAuHw7zm4Gffrh/O2HR3q1KGHDxXMxVC1VpRQDDW\r\n k/VS3Ce2x1gtYDB3q7uuOY8FvtQgTxUYx51JlVKAE8na4XRcZu2DJbtkRvLgWXuBnX+0 Ougg==',
  //     'Authentication-Results':
  //       'mx.google.com; dkim=pass\r\n header.i=@edison-tech.20150623.gappssmtp.com header.s=20150623\r\n header.b=gdijKgPv; arc=pass (i=2 dkim=pass\r\n dkdomain=edison-tech.20150623.gappssmtp.com); spf=neutral (google.com:\r\n 209.85.220.69 is neither permitted nor denied by best guess record for domain\r\n of client+bncbcl2loepzalbbye5ql7qkgqe3m34ynq@edison.tech)\r\n smtp.mailfrom=client+bncBCL2LOEPZALBBYE5QL7QKGQE3M34YNQ@edison.tech',
  //     'DKIM-Signature':
  //       'v=1; a=rsa-sha256; c=relaxed/relaxed;\r\n d=edison-tech.20150623.gappssmtp.com; s=20150623;\r\n h=mime-version:from:date:message-id:subject:to:cc:x-original-sender\r\n :x-original-authentication-results:precedence:mailing-list:list-id\r\n :list-post:list-help:list-archive:list-unsubscribe;\r\n bh=rXAZeCVxn6wh+P35x8yTj/9N1bBeS/hYq9tKvFtQQ/w=;\r\n b=gdijKgPvDUxFjwQ2dWFDzIaROD/nNkOULWEcNjA4sCEe212XYT133nVPDwxERVCYy/\r\n wSONDZrMbLXPgoC4lsiO8wLdDfteaqbe2xYzQoOmFa4d29g+o9XOO9LE7ywm3cYEs4i3\r\n Ar+ynGHQwytBzj6LIx2AvD4mBUfS7Ipc1U4nLSPZSxlnrcLPfxXNDUGKwuiWOdgAeyPL\r\n bri6FdmOQNsyuG0uYTVr3XhD/rG20kW2JG3PcS+jVBy1dnbyogq/6lZt30NJSO86W21l\r\n 1yIvFPppa4uw72XeFl10RLrcM2ypev3e1IPfa/UvMcH4+bo7bWP5AuLlVRWxOhEahL8M UHSg==',
  //     ListId: '<client.edison.tech>',
  //     ListUnsub:
  //       '<mailto:googlegroups-manage+1044890630547+unsubscribe@googlegroups.com>,\r\n <https://groups.google.com/a/edison.tech/group/client/subscribe>',
  //     Received: [
  //       'by 2002:a0c:fa4d:0:0:0:0:0 with SMTP id k13csp4532278qvo; Mon, 21\r\n Dec 2020 04:02:41 -0800 (PST)',
  //       'from mail-sor-f69.google.com (mail-sor-f69.google.com.\r\n [209.85.220.69]) by mx.google.com with SMTPS id\r\n f13sor9183974ioq.81.2020.12.21.04.02.41 for <ruoxi@edison.tech> (Google\r\n Transport Security); Mon, 21 Dec 2020 04:02:41 -0800 (PST)',
  //       'by 2002:a02:cab9:: with SMTP id e25ls4575396jap.9.gmail; Mon, 21 Dec\r\n 2020 04:02:40 -0800 (PST)',
  //       'from mail-sor-f41.google.com (mail-sor-f41.google.com.\r\n [209.85.220.41]) by mx.google.com with SMTPS id\r\n b3sor9033772ioz.19.2020.12.21.04.02.40 for <client@edison.tech> (Google\r\n Transport Security); Mon, 21 Dec 2020 04:02:40 -0800 (PST)',
  //     ],
  //     'Return-Path': '<client+bncBCL2LOEPZALBBYE5QL7QKGQE3M34YNQ@edison.tech>',
  //   };
  //   const headers = [
  //     { type: 0, header: 'From', value: 'ruoxi@edisoon.tech' },
  //     {
  //       type: 1,
  //       header: 'To',
  //       values: ['edison_test@outlook.com', 'easilydo_zhou@163.com'],
  //     },
  //   ];
  //   Object.keys(additionalHeaders).forEach((key) => {
  //     if (typeof additionalHeaders[key] === 'string') {
  //       headers.push({ type: 0, header: key, value: additionalHeaders[key] });
  //     } else {
  //       headers.push({ type: 1, header: key, values: additionalHeaders[key] });
  //     }
  //   });
  //   const extraInfo = { isStrange: false, isColleague: false, isWellKnownProvider: true };
  //   const emailInfo = {
  //     owner: 'qweic@126.com',
  //     body: 'Account is good',
  //     imapHeaders: headers,
  //   };
  //   a8.checkEmail({
  //     emailInfo: emailInfo,
  //     extraCheckInfo: extraInfo,
  //     onOk: (ret) => {
  //       console.log(`bodyPass ${ret.bodyPass}`);
  //       expect(ret.bodyPass).equal(2);
  //       done();
  //     },
  //   });
  // });
  // it('checkEmail: should return 2', function (done) {
  //   this.timeout(5000);
  //   const headers = [{ type: 0, header: 'From', value: 'qweic@163.com' }];
  //   const extraInfo = { isStrange: true, isColleague: false, isWellKnownProvider: false };
  //   const emailInfo = {
  //     owner: 'qweic@126.com',
  //     body: 'Account is good',
  //     imapHeaders: headers,
  //   };
  //   let runA8 = false;
  //   const timer = setInterval(() => {
  //     console.log('interval 300ms');
  //     if (runA8) {
  //       clearInterval(timer);
  //       done();
  //     }
  //   }, 200);
  //   setTimeout(() => {
  //     console.log('running checkEmail');
  //     a8.checkEmail({
  //       emailInfo: emailInfo,
  //       extraCheckInfo: extraInfo,
  //       onOk: (ret) => {
  //         expect(ret.bodyPass).equal(2);
  //         runA8 = true;
  //         console.log('finished running a8');
  //       },
  //     });
  //   }, 800);
  // });
  // it('checkHeader: should throw error', function () {
  //   try {
  //     a8.checkHeader();
  //   } catch (err) {
  //     expect(err.toString()).equal("TypeError: Parameter 'message_header' must be an array");
  //   }
  // });
  it('spamCheck: full run', function (done) {
    this.timeout(35000);
    let count = 0;
    a8.spamCheck({
      emailAddress: 'customerservice2@mp.servicemagic.com',
      replyTo: 'edotest2@126.com',
      onOk: () => {
        console.log('spam check complete');
        expect(0).to.equal(0);
        done();
      },
      onProgress: (data) => {
        count++;
        expect(data.currentCBCount).to.equal(count);
      },
    });
  });
  it('spamCheck, exceeded max wait', function (done) {
    this.timeout(35000);
    const outsideScope = 2;
    const outSideCallback = () => {
      console.log('outside call back');
    };
    a8.spamCheck({
      emailAddress: 'customerservice2@mp.servicemagic.com',
      replyTo: 'edotest2@126.com',
      maxWaitSeconds: 1,
      onOk: (ret) => {
        console.log(`spam check complete ${ret}, outside scope ${outsideScope}`);
        outSideCallback();
        // if(expect){
        //     expect(ret).equal(0);
        // }else {
        //     console.log('no expect function');
        // }
        if (done) {
          done();
          console.log('called done');
        } else {
          console.log('done not present');
        }
      },
      onError: () => {
        console.log('spam check error');
        expect(0).to.equal(0);
        done();
      },
      onProgress: (data) => {
        console.log(`spam check progress ${data.domain}`);
      },
    });
  });
});
