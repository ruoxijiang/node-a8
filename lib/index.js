const a8 = require('bindings')('addon.node');
let initialized = false;
const noOp = () => {};

function checkEmail({
  emailInfo,
  extraCheckInfo,
  onOk = () => {},
  onError = () => {},
  maxWaitSeconds = 90,
} = {}) {
  const onFailed = (data) => {
    if (timer) {
      clearTimeout(timer);
      timer = null;
    }
    if (onError) {
      onError(data);
    }
  };
  const onTimeout = () => {
    timer = null;
    onFailed('Operation time out');
  };
  let timer = setTimeout(onTimeout, maxWaitSeconds * 1000);

  const onComplete = (data) => {
    if (timer) {
      clearTimeout(timer);
      timer = null;
      if (onOk) {
        onOk(data);
      }
    }
  };
  a8.checkEmail(emailInfo, extraCheckInfo, onComplete, onFailed, noOp);
}

function checkHeader({ headers, extraCheckInfo, onOk = () => {}, onError = () => {} } = {}) {
  a8.checkHeader(headers, extraCheckInfo, onOk, onError, noOp);
}
function spamCheck({
  emailAddress,
  replyTo,
  onOk = () => {},
  onError = () => {},
  onProgress = () => {},
  maxWaitSeconds = 90,
} = {}) {
  a8.spamCheck(emailAddress, replyTo, onOk, onError, onProgress, maxWaitSeconds);
}
function fetchLinkedInProfile({
  profile,
  onOk = () => {},
  onError = () => {},
  maxWaitSeconds = 90,
} = {}) {
  const onFailed = (data) => {
    if (timer) {
      clearTimeout(timer);
      timer = null;
    }
    if (onError) {
      onError(data);
    }
  };
  const onTimeout = () => {
    timer = null;
    onFailed('Operation time out');
  };
  let timer = setTimeout(onTimeout, maxWaitSeconds * 1000);
  const onComplete = (data) => {
    if (timer) {
      clearTimeout(timer);
      timer = null;
      if (onOk) {
        onOk(data);
      }
    }
  };
  a8.fetchLinkedInProfile(profile, onComplete, onFailed, noOp);
}

function init({ workingDir, isProduction = false } = {}) {
  if (initialized) {
    return;
  }
  a8.setup(workingDir, isProduction);
  initialized = true;
}

module.exports = {
  init,
  checkEmail,
  checkHeader,
  spamCheck,
  fetchLinkedInProfile,
};
